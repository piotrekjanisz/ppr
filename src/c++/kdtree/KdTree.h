/*
 * KdTree.h
 *
 *  Created on: 08-03-2011
 *      Author: piotrek
 */

#ifndef KDTREE_H_
#define KDTREE_H_

#include <algorithm>
#include <eq/eq.h>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <limits>

template<class ParticleIterator, typename T, int DIM = 3>
class KdTree {
private:
	friend class KdTreeTest;

	template<int DIMM>
	struct KdTreeNode {
		KdTreeNode* left;
		KdTreeNode* right;

		ParticleIterator first;
		ParticleIterator last;

		int dim;

		T bbox_min[DIMM];
		T bbox_max[DIMM];

		vmml::vector<DIMM+1, T> boundingSphere;

		float range[2];

		KdTreeNode(ParticleIterator first, ParticleIterator last, float range_low, float range_high, int dim) :
			left(NULL), right(NULL), first(first), last(last), dim(dim)
		{
			range[0] = range_low;
			range[1] = range_high;
		}

		~KdTreeNode() {
			if (left)
				delete left;
			if (right)
				delete right;
		}

		bool isLeaf() const {
			return !left;
		}
	};

	int _maxParticlesInLeaf;
	KdTreeNode<DIM>* _root;

	KdTreeNode<DIM>* createNodeFromSortedData(ParticleIterator first,
			ParticleIterator last, float range_low, float range_high, int dim);
	int getNextDim(int dim) {
		return (dim + 1) % DIM;
	}

public:
	KdTree(int maxParticlesInLeaf) :
		_maxParticlesInLeaf(maxParticlesInLeaf), _root(0) {
	}

	~KdTree() {
		if (_root)
			delete _root;
	}

	void initializeFromSortedData(ParticleIterator first, ParticleIterator last);

	template <class ParticleRenderer>
	void renderTree(const eq::Matrix4f& projection, const eq::Range&, ParticleRenderer& renderer);

private:
	template <typename V1, typename V2>
	vmml::vector<DIM, T> diff(const V1& v1, const V2& v2);
};

template<class ParticleIterator, typename T, int DIM>
void KdTree<ParticleIterator, T, DIM>::initializeFromSortedData(
		ParticleIterator first, ParticleIterator last)
{
	_root = createNodeFromSortedData(first, last, 0.0f, 1.0f, 0);
}

template <class ParticleIterator, typename T, int DIM>
template <typename V1, typename V2>
vmml::vector<DIM, T> KdTree<ParticleIterator, T, DIM>::diff(const V1& v1, const V2& v2)
{
	vmml::vector<DIM, T> retVal;
	for (int i = 0; i < DIM; i++) {
		retVal[i] = v1[i] - v2[i];
	}
	return retVal;
}

template<class ParticleIterator, typename T, int DIM>
KdTree<ParticleIterator, T, DIM>::KdTreeNode<DIM>* KdTree<ParticleIterator, T,
		DIM>::createNodeFromSortedData(ParticleIterator first, ParticleIterator last, float range_low, float range_high, int dim)
{
	KdTreeNode<DIM>* retVal = new KdTreeNode<DIM> (first, last, range_low, range_high, dim);
	int range = last - first;
	if (range > _maxParticlesInLeaf) {		// node is not a leaf
		retVal->left = createNodeFromSortedData(first, first + range / 2,
				range_low, range_low + (range_high - range_low) / 2, getNextDim(dim));
		retVal->right = createNodeFromSortedData(first + range / 2, last,
				range_low + (range_high - range_low) / 2, range_high, getNextDim(dim));
		for (int i = 0; i < DIM; i++) {
			retVal->bbox_min[i] = std::min(retVal->left->bbox_min[i],
					retVal->right->bbox_min[i]);
			retVal->bbox_max[i] = std::max(retVal->left->bbox_max[i],
					retVal->right->bbox_max[i]);
		}
	} else {								// node is a leaf
		// compute bounding box
		for (int i = 0; i < DIM; i++) {
			retVal->bbox_min[i] = (*first)[i];
			retVal->bbox_max[i] = (*first)[i];
		}
		for (; first != last; ++first) {
			for (int i = 0; i < DIM; i++) {
				if ((*first)[i] > retVal->bbox_max[i]) {
					retVal->bbox_max[i] = (*first)[i];
				} else if ((*first)[i] < retVal->bbox_min[i]) {
					retVal->bbox_min[i] = (*first)[i];
				}
			}
		}
		// compute bounding sphere
		// first get bounding box inner sphere as initial estimate
		T diam = std::numeric_limits<T>::max();
		for (int i = 0; i < DIM; i++) {
			diam = std::min(diam, retVal->bbox_max[i] - retVal->bbox_min[i]);
			retVal->boundingSphere[i] = (retVal->bbox_min[i] + retVal->bbox_max[i]) / 2;
		}
		retVal->boundingSphere[DIM] = diam / 2.0;
		T radius = retVal->boundingSphere[DIM-1];
		T radiusSquared = (diam * diam) / 4.0;
		vmml::vector<DIM, T> center(retVal->boundingSphere.array);
		// expand bounding sphere to contain all outside points
		for (ParticleIterator it = retVal->first; it != retVal->last; ++it) {
			vmml::vector<DIM, T> centerToPoint = diff(*it, center);
			T distanceSquared = centerToPoint.squared_length();
			if (distanceSquared <= radiusSquared)
				continue;

			T distance = sqrtf(distanceSquared);
			T delta = distance - radius;
			T radius = (radius + distance) / 2.0;
			radiusSquared = radius * radius;
			vmml::vector<DIM, T> normDelta = normalize(centerToPoint) * (0.5 * delta);
			center += normDelta;
		}
		for (int i = 0; i < DIM; i++) {
			retVal->boundingSphere[i] = center[i];
		}
		retVal->boundingSphere[DIM] = radius;
	}

	return retVal;
}

template <class ParticleIterator, typename T, int DIM>
template <class ParticleRenderer>
void KdTree<ParticleIterator, T, DIM>::renderTree(const eq::Matrix4f& projection, const eq::Range& range, ParticleRenderer& renderer)
{
	eq::FrustumCullerf culler;
	culler.setup(projection);

	std::vector<KdTreeNode<DIM> > candidates;
	candidates.push_back(_root);

	while (!candidates.empty()) {
		KdTreeNode<DIM>* treeNode = candidates.back();
		candidates.push_back();

		if (treeNode->range[0] >= range.end || treeNode->range[1] < range.start)
			continue;

		const vmml::Visibility visibility = culler.test_sphere(treeNode->boundingSphere);
		switch (visibility) {
		case vmml::VISIBILITY_FULL:
			if (range == eq::Range::ALL ||
					(treeNode->range[0] >= range.start &&
					 treeNode->range[1] < range.end)) {
				renderer.render(treeNode->first, treeNode->last);
				break;
			}
			// fall through to partial visibility
		case vmml::VISIBILITY_PARTIAL:
			if (treeNode->isLeaf()) {
				if (treeNode->range[0] >= range.start) {
					renderer.render(treeNode->first, treeNode->last);
				}
				// drop to be rendered by 'previous' channel
			} else {
				candidates.push_back(treeNode->left);
				candidates.push_back(treeNode->right);
			}
			break;
		case vmml::VISIBILITY_NONE:
			// do nothing
			break;
		}
	}
}

#endif /* KDTREE_H_ */

#pragma once

/**
    This file declares the BVH class which represents a bounding volume hierarchy
    using AABB(Axis Aligned Bounding Box).
    Help taken from https://github.com/VertexC/glass-chess
**/

#include "Acceleration.h"
#include "../utilities/BBox.hpp"

class World;

// node of a BVH Tree
struct Node {
    BBox bbox;
    int start, num_primitives, offset;
};

// node to keep track of objects inside a node
struct BvhEntry {
    int parent;
    int left, right;
};

// node to store traversal information
struct BVHTraversal {
    int i;                // node
    float mint;           // minimum hit time for this node.
    BVHTraversal() {}
    BVHTraversal(int _i, float _mint) : i(_i), mint(_mint) {}
};

class BVH : public Acceleration {
    protected:
        std::vector<Geometry*> geom_array;
        Node* bvhTree;
        int node_num, leaf_num;

    public:
        // constructors
        BVH() = default;
        BVH(World* w_ptr);

        // destructor
        virtual ~BVH();

        void build();
        virtual ShadeInfo hit(const Ray &ray) override;
};

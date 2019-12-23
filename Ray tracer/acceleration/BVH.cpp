#include "BVH.h"
#include <iostream>
#include "../geometry/Geometry.hpp"
#include "../utilities/ShadeInfo.hpp"
#include "../world/World.hpp"

BVH::BVH(World* w_ptr) {
    this->world_ptr = w_ptr;
    geom_array = world_ptr->geometry;
    bvhTree = new Node;
    node_num = 0, leaf_num = 0;
    build();
}

void BVH::build() {
    BvhEntry stackk[64];
    int stack_ptr = 0;

    //Push the root node
    stackk[stack_ptr].left = 0;
    stackk[stack_ptr].right = (int)geom_array.size();
    stackk[stack_ptr].parent = -4;
    stack_ptr++;

    Node node;
    std::vector<Node> nodeList;
    nodeList.reserve(((int)geom_array.size())*2);
    std::cout << geom_array.size() << std::endl;

    while(stack_ptr > 0) {
        BvhEntry &entry(stackk[--stack_ptr]);       //Pop node from stack
        int left = entry.left;
        int right = entry.right;
        int num_primitives = right - left;
        node_num++;
        node.start = left;
        node.num_primitives = num_primitives;
        node.offset = -1;

        // calculate bounding box for node
        BBox object_box(geom_array[left]->getBBox());
        BBox centroid_box(geom_array[left]->getCenter(), geom_array[left]->getCenter());
        for (int i = left + 1; i < right; i++) {
            object_box.extend(geom_array[i]->getBBox());
            centroid_box.extend(geom_array[i]->getCenter());
        }
        node.bbox = object_box;

        // threshold for number of primitives, if <= 4 then it is a leaf
        if (num_primitives <= 4) {
            node.offset = 0;
            leaf_num++;
        }
        nodeList.push_back(node); // push node into nodeList

        if (entry.parent != (-4)) {
            nodeList[entry.parent].offset--;
            if (nodeList[entry.parent].offset == (-3)) {
                nodeList[entry.parent].offset = node_num - 1 - entry.parent;
            }
        }
        // if leaf node
        if (node.offset == 0) continue;

        // getting the split at the center of longest axis and then sorting primitives
        int dim = centroid_box.maxDimension();
        float split = 0.5 * (centroid_box.pmin[dim] + centroid_box.pmax[dim]);
        int mid = left;

        for (int i = left; i < right; i++) {
            if (geom_array[i]->getCenter()[dim] < split) {
                std::swap(geom_array[i], geom_array[mid]);
                mid++;
            }
        }
        // check if mid value is left or right value (not a good value)
        if (mid == left || mid == right) {
            mid = left + (right - left) / 2;        // take mean
        }
        // right child
        stackk[stack_ptr].left = mid;
        stackk[stack_ptr].right = right;
        stackk[stack_ptr].parent = node_num - 1;
        stack_ptr++;
        // left child
        stackk[stack_ptr].left = left;
        stackk[stack_ptr].right = mid;
        stackk[stack_ptr].parent = node_num - 1;
        stack_ptr++;
    }

    // make the tree from node list
    bvhTree = new Node[node_num];
    for (int i = 0; i < node_num; i++) {
        bvhTree[i] = nodeList[i];
    }
    nodeList.clear();
    std::vector<Node>().swap(nodeList);
}

ShadeInfo BVH::hit(const Ray& ray) {
    ShadeInfo s(*world_ptr);
    s.t = kHugeValue;
    BVHTraversal node_stack[64];    // stack for nodes
    int stackptr = 0;

    // push the root node
    node_stack[stackptr].i = 0;
    node_stack[stackptr].mint = kEpsilon;

    Vector3D normal;
    Point3D local_hit;
    float tmin = kEpsilon;

    while(stackptr >= 0) {
        // pop node from stack
        int ni = node_stack[stackptr].i;
        float near = node_stack[stackptr].mint;
        stackptr--;
        const Node &node(bvhTree[ni]);

        if (near > s.t) continue;

        // intersection with leaf
        if (node.offset == 0) {
            for (int i = 0; i < node.num_primitives; i++) {
                ShadeInfo current(*world_ptr);
                const Geometry* g = geom_array[node.start + i];
                float t;
                bool hit = g->hit(ray, t, current);

                // check intersection
                if (hit) {
                    if (current.t < s.t) {
                        s = current;
                        s.hit = true;
                        tmin = t;
                        s.material_ptr = g->get_material();
                        normal = s.normal;
                        local_hit = s.hit_point;
                    }
                }
            }
        } else {                            // intersection with non-leaf
            float left_t, right_t, t0, t1;
            bool left_hit = bvhTree[ni+1].bbox.hit(ray, left_t, t0);
            bool right_hit = bvhTree[ni+node.offset].bbox.hit(ray, right_t, t1);

            if (left_hit && right_hit) {
                // if right child is closer
                if (right_t < left_t) {
                  std::swap(left_t, right_t);
                  std::swap(t0, t1);
                }
                // check for overlaps
                node_stack[++stackptr] = BVHTraversal(ni + 1, right_t);
                node_stack[++stackptr] = BVHTraversal(ni + node.offset, left_t);
            } else if (left_hit) {
                node_stack[++stackptr] = BVHTraversal(ni + 1, left_t);
            } else if (right_hit) {
                node_stack[++stackptr] = BVHTraversal(ni + node.offset, right_t);
            }
        }
    }
    // update shadeinfo values
    if (s.hit) {
        s.t = tmin;
        s.normal = normal;
        s.hit_point = local_hit;
    }
    return s;
}

BVH::~BVH() {
    delete[] bvhTree;
}

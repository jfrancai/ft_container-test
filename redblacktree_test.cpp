#include <gtest/gtest.h>
#include <RedBlackTree.hpp>

/*
 * Test reference : https://google.github.io/googletest/reference/testing.html
 * Test assertion : https://google.github.io/googletest/reference/assertions.html
 */

namespace {

	TEST(TestRBTree, IsExisting) {
		ft::RedBlackTree< int >	rbtree;

		EXPECT_TRUE(rbtree.getRoot());
		EXPECT_FALSE(rbtree.getRoot()->color);
		EXPECT_FALSE(rbtree.getRoot()->right);
		EXPECT_FALSE(rbtree.getRoot()->left);
		EXPECT_FALSE(rbtree.getRoot()->parent);
	}

	TEST(TestRBTree, BasicLeftInsertion) {
		ft::RedBlackTree< int >	rbtree;

		rbtree.insert(42);
		rbtree.insert(41);

		ft::RedBlackTree< int >::node_pointer node(rbtree.getRoot());

		EXPECT_FALSE(node->parent);
		EXPECT_EQ(node->data, 42);

		EXPECT_EQ(node->left->parent, node);
		EXPECT_EQ(node->left->data, 41);
	}

	TEST(TestRBTree, BasicRightInsertion) {
		ft::RedBlackTree< int >	rbtree;

		rbtree.insert(42);
		rbtree.insert(43);

		ft::RedBlackTree< int >::node_pointer node(rbtree.getRoot());

		EXPECT_FALSE(node->parent);
		EXPECT_EQ(node->data, 42);

		EXPECT_EQ(node->right->parent, node);
		EXPECT_EQ(node->right->data, 43);
	}

	TEST(TestRBTree, BasicLeftRotation) {
		ft::RedBlackTree< int >	rbtree;

		rbtree.insert(42);
		rbtree.insert(43);
		rbtree.leftRotate(rbtree.getRoot());

		ft::RedBlackTree< int >::node_pointer node(rbtree.getRoot());

		EXPECT_FALSE(node->parent);
		EXPECT_EQ(node->data, 43);

		EXPECT_EQ(node->left->parent, node);
		EXPECT_EQ(node->left->data, 42);
	}


	TEST(TestRBTree, BasicRightRotation) {
		ft::RedBlackTree< int >	rbtree;

		rbtree.insert(42);
		rbtree.insert(41);
		rbtree.rightRotate(rbtree.getRoot());

		ft::RedBlackTree< int >::node_pointer node(rbtree.getRoot());

		EXPECT_FALSE(node->parent);
		EXPECT_EQ(node->data, 41);

		EXPECT_EQ(node->right->parent, node);
		EXPECT_EQ(node->right->data, 42);
	}

	TEST(TestRBTree, BasicLeftRightInsertion) {
		ft::RedBlackTree< int >	rbtree;

		rbtree.insert(42);
		rbtree.insert(40);
		rbtree.insert(41);

		ft::RedBlackTree< int >::node_pointer node(rbtree.getRoot());

		EXPECT_FALSE(node->parent);
		EXPECT_EQ(node->data, 42);

		EXPECT_EQ(node->left->parent, node);
		EXPECT_EQ(node->left->data, 40);

		EXPECT_EQ(node->left->right->parent, node->left);
		EXPECT_EQ(node->left->right->data, 41);
	}

	TEST(TestRBTree, BasicRightLeftInsertion) {
		ft::RedBlackTree< int >	rbtree;

		rbtree.insert(42);
		rbtree.insert(44);
		rbtree.insert(43);

		ft::RedBlackTree< int >::node_pointer node(rbtree.getRoot());

		EXPECT_FALSE(node->parent);
		EXPECT_EQ(node->data, 42);

		EXPECT_EQ(node->right->parent, node);
		EXPECT_EQ(node->right->data, 44);

		EXPECT_EQ(node->right->left->parent, node->right);
		EXPECT_EQ(node->right->left->data, 43);
	}

	TEST(TestRBTree, BasicLeftRightRotation) {
		ft::RedBlackTree< int >	rbtree;

		rbtree.insert(42);
		rbtree.insert(40);
		rbtree.insert(41);

		ft::RedBlackTree< int >::node_pointer node(rbtree.getRoot());

		ft::RedBlackTree< int >::node_pointer parent(node->parent);
		ft::RedBlackTree< int >::node_pointer phi(node->right);
		ft::RedBlackTree< int >::node_pointer alpha(node->left->left);
		ft::RedBlackTree< int >::node_pointer gama(node->left->right->left);
		ft::RedBlackTree< int >::node_pointer beta(node->left->right->right);

		rbtree.leftRightRotate(rbtree.getRoot());

		node = rbtree.getRoot();

		EXPECT_FALSE(node->parent);
		EXPECT_EQ(node->data, 41);

		EXPECT_EQ(node->left->parent, node);
		EXPECT_EQ(node->left->data, 40);

		EXPECT_EQ(node->right->parent, node);
		EXPECT_EQ(node->right->data, 42);

		EXPECT_EQ(node->parent, parent);
		EXPECT_EQ(node->right->right, phi);
		EXPECT_EQ(node->right->left, gama);
		EXPECT_EQ(node->left->right, beta);
		EXPECT_EQ(node->left->left, alpha);
	}

	TEST(TestRBTree, BasicRightLeftRotation) {
		ft::RedBlackTree< int >	rbtree;

		rbtree.insert(42);
		rbtree.insert(44);
		rbtree.insert(43);
		ft::RedBlackTree< int >::node_pointer node(rbtree.getRoot());

		ft::RedBlackTree< int >::node_pointer parent(node->parent);
		ft::RedBlackTree< int >::node_pointer phi(node->left);
		ft::RedBlackTree< int >::node_pointer alpha(node->right->right);
		ft::RedBlackTree< int >::node_pointer gama(node->right->left->left);
		ft::RedBlackTree< int >::node_pointer beta(node->right->left->right);

		rbtree.rightLeftRotate(rbtree.getRoot());

		node = rbtree.getRoot();

		EXPECT_FALSE(node->parent);
		EXPECT_EQ(node->data, 43);

		EXPECT_EQ(node->left->parent, node);
		EXPECT_EQ(node->left->data, 42);

		EXPECT_EQ(node->right->parent, node);
		EXPECT_EQ(node->right->data, 44);

		EXPECT_EQ(node->parent, parent);
		EXPECT_EQ(node->left->left, phi);
		EXPECT_EQ(node->left->right, gama);
		EXPECT_EQ(node->right->left, beta);
		EXPECT_EQ(node->right->right, alpha);
	}
}  // namespace

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

	TEST(TestRBTree, BasicValid)
	{
		ft::RedBlackTree< int >	rbtree;

		for (int i = 25; i != 0; i--)
				rbtree.insert(i);

		EXPECT_TRUE(rbtree.checker(rbtree.getRoot()));
	}

	TEST(TestRBTree, BasicDeletionOfRedNode)
	{
		ft::RedBlackTree< int >	rbtree;

		for (int i = 5; i != 0; i--)
				rbtree.insert(i);

		rbtree.deleteNode(5);
		EXPECT_TRUE(rbtree.checker(rbtree.getRoot()));
	}

	TEST(TestRBTree, CopyConstructor) {
		ft::RedBlackTree< int >	rbtree;

		for (int i = 5; i != 0; i--)
				rbtree.insert(i);

		ft::RedBlackTree< int >	rbtree2(rbtree);
		rbtree2.printTree();
		rbtree.printTree();

		EXPECT_TRUE(rbtree.checker(rbtree2.getRoot()));
	}

	TEST(TestRBTree, AssignmentOperator) {
		ft::RedBlackTree< int >	rbtree;

		for (int i = 5; i != 0; i--)
				rbtree.insert(i);

		ft::RedBlackTree< int >	rbtree2;
		rbtree2 = rbtree;
		rbtree2.printTree();
		rbtree.printTree();

		EXPECT_TRUE(rbtree.checker(rbtree2.getRoot()));
	}
}  // namespace

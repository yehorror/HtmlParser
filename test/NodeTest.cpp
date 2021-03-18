#include <gtest/gtest.h>
#include "Node.hpp"

using namespace HtmlParser;

TEST(NodeTest, TestSetAndGetValue)
{
    const std::string VALUE = "value";

    Node node;
    node.SetValue(VALUE);

    const std::string nodeValue = node.GetValue();

    EXPECT_EQ(VALUE, nodeValue);
}

TEST(NodeTest, TestNodeEquality)
{
    const std::string TEST_VALUE = "Test value";
    Tag firstTag, secondTag;
    Node firstNode, secondNode;

    firstNode.SetValue(TEST_VALUE);
    firstTag.SetAttribute(TEST_VALUE, TEST_VALUE);
    firstTag.SetName(TEST_VALUE);
    firstNode.SetTag(firstTag);

    secondNode.SetValue(TEST_VALUE);
    secondTag.SetAttribute(TEST_VALUE, TEST_VALUE);
    secondTag.SetName(TEST_VALUE);
    secondNode.SetTag(secondTag);

    EXPECT_EQ(firstNode, secondNode);
}

TEST(NodeTest, TestNodeNotEquality)
{
    const std::string TEST_VALUE1 = "Test value1";
    const std::string TEST_VALUE2 = "Test value2";
    Tag firstTag, secondTag;
    Node firstNode, secondNode;

    firstNode.SetValue(TEST_VALUE1);
    firstTag.SetAttribute(TEST_VALUE1, TEST_VALUE1);
    firstTag.SetName(TEST_VALUE1);
    firstNode.SetTag(firstTag);

    secondNode.SetValue(TEST_VALUE2);
    secondTag.SetAttribute(TEST_VALUE2, TEST_VALUE2);
    secondTag.SetName(TEST_VALUE2);
    secondNode.SetTag(secondTag);

    EXPECT_NE(firstNode, secondNode);
}

TEST(NodeTest, TestAppendOfChildNode)
{
    const std::string CHILD_NODE_VALUE = "Test";
    const std::string SECOND_CHILD_NODE_VALUE = "Test2";

    Node parentNode;

    Node childNode_;
    childNode_.SetValue(CHILD_NODE_VALUE);
    parentNode.AppendChild(childNode_);

    Node secondChildNode_;
    secondChildNode_.SetValue(SECOND_CHILD_NODE_VALUE);
    parentNode.AppendChild(secondChildNode_);

    Node& childNode = parentNode.GetChildNode(0);
    Node& secondChildNode = parentNode.GetChildNode(1);

    EXPECT_EQ(childNode, childNode_);
    EXPECT_EQ(secondChildNode, secondChildNode_);
}

TEST(NodeTest, TestNodeEmpty)
{
    Node emptyNode;
    EXPECT_TRUE(emptyNode.Empty());
}

TEST(NodeTest, TestNodeNotEmpty)
{
    Node emptyNode;
    
    Node childNode;
    emptyNode.AppendChild(childNode);

    EXPECT_FALSE(emptyNode.Empty());
}

TEST(NodeTest, TestRemoveChildNodeByIndex)
{
    const std::string FIRST_CHILD_NODE_VALUE = "Test";
    const std::string SECOND_CHILD_NODE_VALUE = "Test2";

    Node parentNode;

    Node firstChildNode_;
    firstChildNode_.SetValue(FIRST_CHILD_NODE_VALUE);

    Node secondChildNode_;
    secondChildNode_.SetValue(SECOND_CHILD_NODE_VALUE);

    parentNode.AppendChild(firstChildNode_);
    parentNode.AppendChild(secondChildNode_);
    parentNode.RemoveChild(0);

    Node& childNode = parentNode.GetChildNode(0);
    EXPECT_EQ(childNode, secondChildNode_);
}

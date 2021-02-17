#include <gtest/gtest.h>
#include "Node.hpp"

using namespace HtmlParser;

TEST(NodeTest, TestSetAndGetTagName)
{
    const std::string TAG_NAME = "test";

    Node node;
    node.SetTagName(TAG_NAME);

    const std::string nodeTagName = node.GetTagName();

    EXPECT_EQ(TAG_NAME, nodeTagName);
}

TEST(NodeTest, TestAddingAngSettingOfAnAttributes)
{
    const std::string FIRST_ATTRIBUTE_NAME = "attribute1";
    const std::string FIRST_ATTRIBUTE_VALUE = "value1";

    const std::string SECOND_ATTRIBUTE_NAME = "attribute2";
    const std::string SECOND_ATTRIBUTE_VALUE = "value2";

    Node node;
    node.SetAttribute(FIRST_ATTRIBUTE_NAME, FIRST_ATTRIBUTE_VALUE);
    node.SetAttribute(SECOND_ATTRIBUTE_NAME, SECOND_ATTRIBUTE_VALUE);

    const std::string nodeFirstAttributeValue = node.GetAttribute(FIRST_ATTRIBUTE_NAME);
    const std::string nodeSecondAttributeValue = node.GetAttribute(SECOND_ATTRIBUTE_NAME);

    EXPECT_EQ(FIRST_ATTRIBUTE_VALUE, nodeFirstAttributeValue);
    EXPECT_EQ(SECOND_ATTRIBUTE_VALUE, nodeSecondAttributeValue);
}

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
    Node firstNode, secondNode;

    firstNode.SetValue(TEST_VALUE);
    firstNode.SetAttribute(TEST_VALUE, TEST_VALUE);
    firstNode.SetTagName(TEST_VALUE);

    secondNode.SetValue(TEST_VALUE);
    secondNode.SetAttribute(TEST_VALUE, TEST_VALUE);
    secondNode.SetTagName(TEST_VALUE);

    EXPECT_EQ(firstNode, secondNode);
}

TEST(NodeTest, TestNodeNotEquality)
{
    const std::string TEST_VALUE1 = "Test value1";
    const std::string TEST_VALUE2 = "Test value2";
    Node firstNode, secondNode;

    firstNode.SetValue(TEST_VALUE1);
    firstNode.SetAttribute(TEST_VALUE1, TEST_VALUE1);
    firstNode.SetTagName(TEST_VALUE1);

    secondNode.SetValue(TEST_VALUE2);
    secondNode.SetAttribute(TEST_VALUE2, TEST_VALUE2);
    secondNode.SetTagName(TEST_VALUE2);

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

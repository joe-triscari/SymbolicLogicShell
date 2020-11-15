using System;
using System.Collections.Generic;

namespace LogicExpression
{
    internal static class ExpressionParser
    {
        public static (ExpressionNode, Operands) Parse(string expression)
        {
            CheckExpression(expression, out var operands);

            return (ParseExpression(expression), operands);
        }

        private static void CheckExpression(string expression, out Operands operands)
        {
            int leftParenthesesCount = 0;
            int rightParenthesesCount = 0;
            char lastChar = '\0';

            operands = new Operands();

            int len = expression.Length;
            for (int i = 0; i < len; ++i)
            {
                char c = expression[i];

                if (c == ' ' || c == '\t' ||
                    c == 'T' || c == 'F' ||
                    c == '1' || c == '0')
                {
                    lastChar = c;
                    continue;
                }

                bool validChar = c == '(' || c == ')' || Operand.IsValid(c) || Operators.IsValid(c);
                if (validChar)
                {
                    if (c == '(')
                    {
                        ++leftParenthesesCount;
                    }
                    else if (c == ')')
                    {
                        ++rightParenthesesCount;
                    }
                    else if (Operand.IsValid(c))
                    {
                        operands.Add(new Operand(c));
                    }
                    else if (Operators.IsValid(c))
                    {
                        if (Operators.IsValid(lastChar))
                        {
                            throw new ArgumentException($"Position {i}: Operator not expected.");
                        }
                    }
                }
                else
                {
                    throw new ArgumentException($"Position {i}: Invalid char '{c}'.");
                }

                lastChar = c;
            }

            if(leftParenthesesCount != rightParenthesesCount)
            {
                throw new ArgumentException($"Invalid Expression - Mismatched parentheses.");
            }
        }

        private static ExpressionNode ParseExpression(string expression)
        {
            int leftParenthesisCount = 0;
            var operators = new Stack<char>();
            var nodes = new Stack<ExpressionNode>();

            int len = expression.Length;
            for (int i = 0; i < len; ++i)
            {
                char c = expression[i];
                if (c == ' ' || c == '\t')
                {
                    continue;
                }

                if (c == '(') 
                {
                    leftParenthesisCount++;
                }
                else if (Operators.IsValid(c))
                {
                    operators.Push(c);
                }
                else if (c == ')') 
                {
                    leftParenthesisCount--;
                    if (operators.Count > 0)
                    {
                        char cOperator = operators.Pop();

                        nodes.Push(
                            new OperatorNode(cOperator)
                            {
                                RightChild = nodes.Pop(),
                                LeftChild = Operators.IsUnary(cOperator) ? null : nodes.Pop()
                            });
                    }
                }
                else
                {
                    nodes.Push(new OperandNode(c));
                }
            }

            if (leftParenthesisCount != 0 || operators.Count > 0)
            {
                throw new ArgumentException("Invalid Expression.");
            }

            return nodes.Pop();
        }
    }
}
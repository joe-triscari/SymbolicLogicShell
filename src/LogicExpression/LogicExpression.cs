using System;
using System.Collections.Generic;
using System.Data;

namespace LogicExpression
{
    public class LogicExpression
    {
        private readonly ExpressionNode _node;
        private readonly Operands _operands;

        private LogicExpression(ExpressionNode node, Operands operands)
        {
            _node = node;
            _operands = operands;
        }

        public static LogicExpression Create(string expression)
        {
            var (node, operands) = ExpressionParser.Parse(expression);

            return new LogicExpression(node, operands) {Expression = expression};
        }

        public static bool IsValid(string expression, out string validationMessage)
        {
            validationMessage = "";

            try
            {
                ExpressionParser.Parse(expression);
            }
            catch (ArgumentException e)
            {
                validationMessage = e.Message;
                return false;
            }

            return true;
        }

        public string Expression { get; private set; }
        public Operands Operands => _operands;

        public char MajorOperator => Operators.IsValid(_node.Symbol) ? _node.Symbol : ' ';

        public override string ToString()
        {
            return Expression??"";
        }

        public bool GetTruthValue()
        {
            return _node.GetValue(_operands);
        }

        public bool GetTruthValue(Operands operands)
        {
            return _node.GetValue(operands);
        }

        public bool GetTruthValue(int mask)
        {
            _operands.SetValues(mask);
            return _node.GetValue(_operands);
        }

        public LogicExpression Conjunction(LogicExpression e)
        {
            return Create($"({Expression}&{e.Expression})");
        }

        public LogicExpression Disjunction(LogicExpression e)
        {
            return Create($"({Expression}|{e.Expression})");
        }

        public LogicExpression Negation()
        {
            return Create($"(!{Expression})");
        }

        public bool LogicallyEquivalent(LogicExpression e)
        {
            var ops = _operands + e._operands;

            var n = ops.GetCombinations();
            for (int l = 0; l < n; ++l)
            {
                ops.SetValues(l);
                if (GetTruthValue(ops) != e.GetTruthValue(ops))
                {
                    return false;
                }
            }

            return true;
        }

        public bool LogicallyImplies(LogicExpression e)
        {
            var ops = _operands + e._operands;
            var n = ops.GetCombinations();

            for (int l = 0; l < n; ++l)
            {
                ops.SetValues(l);
                if (GetTruthValue(ops) && !e.GetTruthValue(ops))
                {
                    return false;
                }
            }

            return true;
        }

        public bool IsTautology()
        {
            var n = _operands.GetCombinations();
            for (int l = 0; l < n; ++l)
            {
                if (!GetTruthValue(l))
                {
                    return false;
                }
            }

            return true;
        }

        public bool IsContradiction()
        {
            var n = _operands.GetCombinations();
            for (int l = 0; l < n; ++l)
            {
                if (GetTruthValue(l))
                {
                    return false;
                }
            }

            return true;
        }

        public string GetPropositionText()
        {
            var n = _operands.GetCombinations();
            bool alwaysTrue = true;
            bool alwaysFalse = true;

            for (int l = 0; l < n; ++l)
            {
                var b = GetTruthValue(l);

                if (!b)
                {
                    alwaysTrue = false;
                }

                if (b)
                {
                    alwaysFalse = false;
                }

            }

            return alwaysTrue ? "Tautology" : alwaysFalse ? "Contradiction" : "Contingency";
        }

        public static LogicExpression operator& (LogicExpression e1, LogicExpression e2)
        {
            return e1?.Conjunction(e2);
        }

        public static LogicExpression operator |(LogicExpression e1, LogicExpression e2)
        {
            return e1?.Disjunction(e2);
        }

        public static LogicExpression operator !(LogicExpression e1)
        {
            return e1?.Negation();
        }

        public static bool operator >(LogicExpression e1, LogicExpression e2)
        {
            return e1.LogicallyImplies(e2);
        }

        public static bool operator <(LogicExpression e1, LogicExpression e2)
        {
            return e2.LogicallyImplies(e1);
        }

        //public static bool operator ==(LogicExpression e1, LogicExpression e2)
        //{
        //    if (e1 == null || e2 == null)
        //    {
        //        return false;
        //    }

        //    return e1.LogicallyEquivalent(e2);
        //}

        //public static bool operator !=(LogicExpression e1, LogicExpression e2)
        //{
        //    if (e1 == null || e2 == null)
        //    {
        //        return false;
        //    }

        //    return !(e1 == e2);
        //}

        public List<string> GetSubExpressions()
        {
            var subExpressions = new List<string>();

            if (MajorOperator == ' ')
            {
                subExpressions.Add(Expression);
            }
            else
            {
                _getSubExpressions(_node, subExpressions);
            }

            return subExpressions;
        }

        private string _getSubExpressions(ExpressionNode root, List<string> subExpressions)
        {
            string c;
            if (root.RightChild != null)
            {
                string leftExpression;
                if (root.LeftChild != null)
                {
                    leftExpression = _getSubExpressions(root.LeftChild, subExpressions);
                    var rightExpression = _getSubExpressions(root.RightChild, subExpressions);

                    c = $"({leftExpression}{root.Symbol}{rightExpression})";
                    subExpressions.Add(c);
                }
                else
                {
                    leftExpression = _getSubExpressions(root.RightChild, subExpressions);

                    c = $"({root.Symbol}{leftExpression})";
                    subExpressions.Add(c);
                }
            }
            else
            {
                c = "" + root.Symbol;
            }

            return c;
        }
    }
}
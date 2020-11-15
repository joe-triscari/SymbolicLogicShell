namespace LogicExpression
{
    internal abstract class ExpressionNode
    {
        protected ExpressionNode(char symbol)
        {
            Symbol = symbol;
        }

        public ExpressionNode LeftChild { get; set; }
        public ExpressionNode RightChild { get; set; }
        public char Symbol { get; private set; }

        public abstract bool GetValue(Operands operands);

        protected static bool Evaluate(bool bOp1, bool bOp2, char operatorSymbol)
        {
            switch (operatorSymbol)
            {
                case Operators.And:
                    return bOp1 && bOp2;
                case Operators.Nand:
                    return !(bOp1 && bOp2);
                case Operators.Or:
                    return bOp1 || bOp2;
                case Operators.Nor:
                    return !(bOp1 || bOp2);
                case Operators.Not:
                    return !bOp1;
                case Operators.Conditional:
                {
                    if (bOp1 && !bOp2) return false;
                    return true;
                }
                case Operators.Xor:
                {
                    return (bOp1 || bOp2) && (!bOp1 || !bOp2);
                }
                case Operators.BiConditional:
                {
                    return bOp1 && bOp2 || !bOp1 && !bOp2;
                }
                default:
                    return false;
            }
        }
    }

    internal class OperandNode : ExpressionNode
    {
        public OperandNode(char symbol) : base(symbol) { }

        public override bool GetValue(Operands operands)
        {
            return operands.ValueOf(Symbol);
        }
    }

    internal class OperatorNode : ExpressionNode
    {
        public OperatorNode(char symbol) : base(symbol)
        {
        }

        public override bool GetValue(Operands operands)
        {
            return EvaluateTree(this, operands);
        }

        private static bool EvaluateTree(ExpressionNode node, Operands operands)
        {
            bool bVal;

            if (node.RightChild != null)
            {
                bool bOp1;
                if (node.LeftChild != null)
                {
                    bOp1 = EvaluateTree(node.LeftChild, operands);
                    bool bOp2 = EvaluateTree(node.RightChild, operands);
                    bVal = Evaluate(bOp1, bOp2, node.Symbol);
                }
                else
                {
                    bOp1 = EvaluateTree(node.RightChild, operands);
                    bVal = Evaluate(bOp1, false, node.Symbol);
                }
            }
            else
            {
                bVal = node.GetValue(operands);
            }

            return bVal;
        }
    }
}
using System;
using System.Collections.Generic;

namespace SymbolicLogicLib
{
    public class TruthTableBuilder
    {
        public void WriteTruthTable(LogicExpression expression, ITruthTableWriter writer, bool includeSubExpressions = true)
        {
            if (expression == null)
            {
                throw new ArgumentNullException(nameof(expression));
            }

            if (writer == null)
            {
                throw new ArgumentNullException(nameof(writer));
            }

            writer.WriteTableStart();

            var expressions = (includeSubExpressions ? expression.GetSubExpressions() : new List<string> { expression.Expression }).ConvertAll(LogicExpression.Create);

            writer.WriteHeaderStart(expressions.Count);
            writer.WriteHeaderOperands(expression.Operands);

            foreach (var subExpression in expressions)
            {
                writer.WriteHeaderExpression(subExpression.Expression);
            }

            writer.WriteHeaderEnd();

            int combos = expression.Operands.GetCombinations();
            int variableCount = expression.Operands.Count;
            var truthValues = new bool[variableCount];

            int row = 1;
            for(int i = combos-1; i >= 0; i--)
            {
                writer.WriteRowStart(row);

                for (int k = 0; k < variableCount; k++)
                {
                    truthValues[k] = (combos & (i << k + 1)) != 0;
                }

                writer.WriteRowTruthValues(row, truthValues);

                var operands = expression.Operands.Clone();
                operands.SetValues(truthValues);

                foreach (var subExpression in expressions)
                {
                    writer.WriteRowExpressionValue(row, subExpression, subExpression.GetTruthValue(operands));
                }

                writer.WriteRowEnd(row);

                row += 1;
            }

            writer.WriteTableEnd();
        }
    }
}
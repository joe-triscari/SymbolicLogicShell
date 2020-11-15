using System;
using System.Collections.Generic;

namespace LogicExpression
{
    public class TruthTableBuilder
    {
        public void BuildTruthTable(LogicExpression expression, ITruthTableWriter writer, bool includeSubExpressions = true)
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

            var expressions = includeSubExpressions ? expression.GetSubExpressions() : new List<string> { expression.Expression };

            writer.WriteHeaderStart(expressions.Count);
            writer.WriteHeaderOperands(expression.Operands);

            foreach (var subExpression in expressions)
            {
                writer.WriteHeaderExpression(subExpression);
            }

            writer.WriteHeaderEnd();

            int combos = expression.Operands.GetCombinations();
            int variableCount = expression.Operands.Count;

            int row = 1;
            for(int i = combos-1; i >= 0; i--)
            {
                writer.WriteRowStart(row);

                var truthValues = new bool[variableCount];
                for (int k = 0; k < variableCount; k++)
                {
                    truthValues[k] = (combos & (i << k + 1)) != 0;
                }

                writer.WriteRowTruthValues(row, truthValues);

                var operands = expression.Operands.Clone();
                operands.SetValues(truthValues);

                foreach (var subExpression in expressions)
                {
                    var logicExpression = LogicExpression.Create(subExpression);
                    writer.WriteRowExpressionValue(row, logicExpression, logicExpression.GetTruthValue(operands));
                }

                writer.WriteRowEnd(row);

                row += 1;
            }

            writer.WriteTableEnd();
        }
    }
}
namespace LogicExpression
{
    public interface ITruthTableWriter
    {
        void WriteTableStart();
        void WriteTableEnd();

        void WriteHeaderStart(int expressionCount);
        void WriteHeaderOperands(Operands operands);
        void WriteHeaderExpression(string expression);
        void WriteHeaderEnd();

        void WriteRowStart(int row);
        void WriteRowTruthValues(int row, bool[] values);
        void WriteRowExpressionValue(int row, LogicExpression expression, bool value);
        void WriteRowEnd(int row);
    }
}
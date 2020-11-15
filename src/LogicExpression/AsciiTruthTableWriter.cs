using System;
using System.IO;
using System.Text;

namespace LogicExpression
{
    public class AsciiTruthTableWriter : ITruthTableWriter
    {
        private readonly TextWriter _textWriter;
        private readonly StringBuilder _headerLine = new StringBuilder();

        public AsciiTruthTableWriter(TextWriter textWriter)
        {
            _textWriter = textWriter ?? Console.Out;
        }

        public void WriteTableStart()
        {
            Console.ForegroundColor = ConsoleColor.Cyan;
        }

        public void WriteTableEnd()
        {
            Console.ResetColor();
            _textWriter.Flush();
        }

        public void WriteHeaderStart(int expressionCount)
        {
        }

        public void WriteHeaderOperands(Operands operands)
        {
            foreach (var operand in operands)
            {
                _textWriter.Write(operand);
                _headerLine.Append('-');
            }
            _textWriter.Write(" |");
            _headerLine.Append("-|");
        }

        public void WriteHeaderExpression(string expression)
        {
            var text = $" {expression} |";
            _textWriter.Write(text);
            _headerLine.Append(new string('-', text.Length-1));
            _headerLine.Append('|');
        }

        public void WriteHeaderEnd()
        {
            _textWriter.Write(Environment.NewLine);
            _textWriter.Write(_headerLine);
            _textWriter.Write(Environment.NewLine);
        }

        public void WriteRowStart(int row)
        {
        }

        public void WriteRowTruthValues(int row, bool[] values)
        {
            foreach (var value in values)
            {
                _textWriter.Write(value ? 'T' : 'F');
            }
            _textWriter.Write(" |");
        }

        public void WriteRowExpressionValue(int row, LogicExpression expression, bool value)
        {
            int width = expression.Expression.Length + 2;
            int mid = width / 2;
            char valueChar = value ? 'T' : 'F';

            for (int i = 0; i < width; i++)
            {
                _textWriter.Write(i == mid ? valueChar : ' ');
            }

            _textWriter.Write('|');
        }

        public void WriteRowEnd(int row)
        {
            _textWriter.Write(Environment.NewLine);
        }
    }
}
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
            var shortened = RemoveRedundantParenthesis(expression);
            var highlightIndex = GetMajorOperatorIndex(shortened);
            var color = Console.ForegroundColor;

            var textChars = $" {shortened} |".ToCharArray();
            for (int i = 0; i < textChars.Length; i++)
            {
                if (i == highlightIndex+1)
                {
                    Console.ForegroundColor = ConsoleColor.DarkYellow;
                    _textWriter.Write(textChars[i]);
                    Console.ForegroundColor = color;
                }
                else
                {
                    _textWriter.Write(textChars[i]);
                }
            }
            
            //  _textWriter.Write(text);
            _headerLine.Append(new string('-', textChars.Length-1));
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
            int width = RemoveRedundantParenthesis(expression.Expression).Length + 2;
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

        private string RemoveRedundantParenthesis(string expression)
        {
            if (string.IsNullOrWhiteSpace(expression))
            {
                return expression;
            }

            if (expression.Length < 3)
            {
                return expression;
            }

            if (expression[0] == '(' && expression[^1] == ')')
            {
                return expression.Substring(1, expression.Length - 2);
            }

            return expression;
        }

        private int GetMajorOperatorIndex(string expression)
        {
            var chars = expression.ToCharArray();
            int leftParCount = 0;

            for (int i = 0; i < chars.Length; i++)
            {
                char c = chars[i];

                switch (c)
                {
                    case '(':
                        leftParCount += 1;
                        break;
                    case ')':
                        leftParCount -= 1;
                        break;
                    default:

                        if (Operators.IsValid(c) && leftParCount == 0)
                        {
                            return i;
                        }

                        break;
                }
            }

            return -1;
        }
    }
}
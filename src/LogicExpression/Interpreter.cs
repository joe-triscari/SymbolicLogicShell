using System;
using System.IO;

namespace SymbolicLogicShell
{
    public class Interpreter
    {
        private readonly TextReader _textReader;
        private readonly TextWriter _textWriter;

        public Interpreter(TextReader textReader = null, TextWriter textWriter = null)
        {
            _textReader = textReader ?? Console.In;
            _textWriter = textWriter ?? Console.Out;
        }

        public string Prompt { get; set; } = "$";

        public void Loop()
        {
            while (true)
            {
                string input = ReadUserInput();
            }
        }

        private string ReadUserInput()
        {
            string userInput;

            do
            {
                _textWriter.Write(Prompt);
                _textWriter.Write(' ');

                userInput = _textReader.ReadLine()?.Trim() ?? "";

            } while (string.IsNullOrEmpty(userInput));

            return userInput;
        }
    }
}
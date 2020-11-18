using System;
using System.Collections.Generic;
using System.Linq;
using SymbolicLogicLib;

namespace SymbolicLogicShell
{
    class Program
    {
        private static readonly Dictionary<string, string> Definitions = new Dictionary<string, string>();
        private static readonly Dictionary<string, Action<string[]>> Commands = new Dictionary<string, Action<string[]>>(StringComparer.OrdinalIgnoreCase);

        static void Main(string[] args)
        {
            Commands.Add("def", Define);
            Commands.Add("cls", args => {Console.Clear();});
            Commands.Add("?", EvaluateTruth);
            Commands.Add("sub", PrintSubExpressions);
            Commands.Add("print", PrintTruthTable);

            while (true)
            {
                Console.Write('$');
                Console.Write(' ');
                var commandText = Console.ReadLine()?.Trim()??"";
                if (string.IsNullOrEmpty(commandText))
                {
                    continue;
                }

                if (commandText.Equals("exit", StringComparison.CurrentCultureIgnoreCase) ||
                    commandText.Equals("quit", StringComparison.CurrentCultureIgnoreCase))
                {
                    break;
                }

                var parts = commandText.Split(new[] {' '}, StringSplitOptions.RemoveEmptyEntries);
                var command = parts[0].Trim();
                var commandArgs = parts.Skip(1).ToArray();

                if (!Commands.ContainsKey(command))
                {
                    Console.WriteLine($"Command '{command}' not defined.");
                    continue;
                }

                try
                {
                    Commands[command](commandArgs);
                }
                catch (ArgumentException e)
                {
                    Console.WriteLine(e.Message);
                }
            }

            Console.WriteLine("Bye");
        }

        static void Define(string[] args)
        {
            if (args.Length == 0)
            {
                // Dump all variables.
                foreach (var definition in Definitions)
                {
                    var exp = LogicExpression.Create(definition.Value);
                    Console.WriteLine($"=> {definition.Key} = {definition.Value} ({exp.GetPropositionText()})");
                }

                return;
            }

            var temp = string.Join(' ', args);
            var parts = temp.Split('=', StringSplitOptions.RemoveEmptyEntries);

            if (parts.Length != 2)
            {
                throw new ArgumentException("Incorrect syntax. Expected: def [variable] = [expression].");
            }

            var variable = parts[0].Trim();
            if (variable.IndexOf(' ') >= 0)
            {
                throw new ArgumentException("Variable name must not contain spaces.");
            }

            var expression = parts[1].Trim();

            // Substitution
            foreach (var definition in Definitions)
            {
                expression = expression.Replace(definition.Key, definition.Value, StringComparison.CurrentCultureIgnoreCase);
            }

            if (!LogicExpression.IsValid(expression, out string validationMessage))
            {
                Console.WriteLine($"Invalid expression: {validationMessage}");
                return;
            }

            if (Definitions.ContainsKey(variable))
            {
                Definitions[variable] = expression;
            }
            else
            {
                Definitions.Add(variable, expression);
            }

            Console.WriteLine($"=> {variable} = {expression}");
        }

        static void EvaluateTruth(string[] args)
        {
            if (args.Length == 0)
            {
                throw new ArgumentException("Expected expression.");
            }

            var expression = string.Join(' ', args);
            if (!LogicExpression.IsValid(expression, out string validationMessage))
            {
                Console.WriteLine($"Invalid expression: {validationMessage}");
                return;
            }

            var argument = new LogicArgument();
            foreach (var definition in Definitions)
            {
                argument.AddPremise(LogicExpression.Create(definition.Value));
            }
            argument.SetConclusion(LogicExpression.Create(expression));

            Console.WriteLine(argument.IsValid());

            var truthTableBuilder = new TruthTableBuilder();

            truthTableBuilder.WriteTruthTable(LogicExpression.Create(argument.ToExpression()), new AsciiTruthTableWriter(Console.Out));
        }

        static void PrintSubExpressions(string[] args)
        {
            if (args.Length == 0)
            {
                throw new ArgumentException("Expected expression.");
            }

            var expressionSyntax = string.Join(' ', args);
            if (!LogicExpression.IsValid(expressionSyntax, out string validationMessage))
            {
                Console.WriteLine($"Invalid expression: {validationMessage}");
                return;
            }

            var expression = LogicExpression.Create(expressionSyntax);
            var subExpressions = expression.GetSubExpressions();
            foreach (var subExpression in subExpressions)
            {
                Console.WriteLine($"=> {subExpression}");
            }
        }

        static void PrintTruthTable(string[] args)
        {
            if (args.Length == 0)
            {
                throw new ArgumentException("Expected expression.");
            }

            var expressionSyntax = string.Join(' ', args);
            if (!LogicExpression.IsValid(expressionSyntax, out string validationMessage))
            {
                Console.WriteLine($"Invalid expression: {validationMessage}");
                return;
            }

            var expression = LogicExpression.Create(expressionSyntax);
            var truthTableBuilder = new TruthTableBuilder();

            truthTableBuilder.WriteTruthTable(expression, new AsciiTruthTableWriter(Console.Out));
        }
    }
}

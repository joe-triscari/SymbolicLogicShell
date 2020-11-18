using System.IO;

namespace SymbolicLogicShell.Commands
{
    public interface IShellCommand
    {
        public string Name { get; }
        public string Description { get; }

        public void Execute(string[] args);

        public void ShowHelp(TextWriter textWriter);
    }
}
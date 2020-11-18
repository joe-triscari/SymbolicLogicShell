using System.Runtime.CompilerServices;

namespace SymbolicLogicLib
{
    public static class Operators
    {
        public const char Not = '!';
        public const char And = '&';
        public const char Or = '|';
        public const char Conditional = '>';
        public const char Xor = '^';
        public const char BiConditional = '=';
        public const char Nand = '$';
        public const char Nor = '%';

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static bool IsValid(char c)
        {
            return c == Not || c == And || c == Or || c == Conditional || c == Xor || c == BiConditional || c == Nand || c == Nor;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static bool IsUnary(char c)
        {
            return c == Not;
        }
    }
}
using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace LogicExpression
{
    public struct Operand : IComparable<Operand>
    {
        public char Symbol { get; }
        public bool Value { get; set; }

        public Operand(char symbol)
        {
            Symbol = symbol;
            Value = false;
        }

        public int CompareTo(Operand other)
        {
            return Symbol.CompareTo(other.Symbol);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
        public static bool IsValid(char c)
        {
            return c >= 'a' && c <= 'z';
        }
    }

    public class Operands : IEnumerable<char>
    {
        private const int OPCOUNT = 26;

        private readonly bool?[] _operands = new bool?[OPCOUNT];
        private int? _combinationCount = null;

        public int Count { get; private set; }

        [MethodImpl(MethodImplOptions.AggressiveInlining | MethodImplOptions.AggressiveOptimization)]
        public int GetCombinations()
        {
            if (_combinationCount == null)
            {
                _combinationCount = (int)Math.Pow(2, Count);
            }

            return _combinationCount.Value;
        }

        public int Add(Operand operand)
        {
            int index = operand.Symbol - 'a';

            if (_operands[index] == null)
            {
                Count += 1;
                _combinationCount = null;
                _operands[index] = operand.Value;
            }

            return Count;
        }

        public void Clear()
        {
            for (int i = 0; i < OPCOUNT; i++)
            {
                _operands[i] = null;
            }
            Count = 0;
            _combinationCount = null;
        }

        public void CloneTo(Operands operands)
        {
            if (operands != this)
            {
                operands.Count = Count;
                operands._combinationCount = null;

                for (int i = 0; i < OPCOUNT; ++i)
                {
                    operands._operands[i] = _operands[i];
                }
            }
        }

        public Operands Clone()
        {
            var operands = new Operands {Count = Count};
            for (int i = 0; i < OPCOUNT; ++i)
            {
                operands._operands[i] = _operands[i];
            }

            return operands;
        }

        public int Combine(Operands operands)
        {
            if (operands != this)
            {
                for (int i = 0; i < OPCOUNT; ++i)
                {
                    if (operands._operands[i] != null && _operands[i] == null)
                    {
                        _operands[i] = operands._operands[i];
                        Count += 1;
                        _combinationCount = null;
                    }
                }
            }

            return Count;
        }

        public bool ValueOf(char c)
        {
            if (c == '1' || c == 'T') return true;
            if (c == '0' || c == 'F') return false;

            return _operands[c - 'a'] == true;
        }

        public void SetValueOf(char c, bool b)
        {
            _operands[c - 'a'] = b;
        }

        public void SetValues(int mask)
        {
            int offset = 1;
            int n = GetCombinations();

            for (int i = 0; i < OPCOUNT; ++i)
            {
                if (_operands[i] != null)
                {
                    _operands[i] = (n & (mask << offset++)) != 0;
                }
            }
        }

        public void SetValues(bool[] values)
        {
            if (Count != values.Length)
            {
                throw new ArgumentOutOfRangeException($"Expected array length of {Count}.");
            }

            int index = 0;
            for (int i = 0; i < OPCOUNT; ++i)
            {
                if (_operands[i] != null)
                {
                    _operands[i] = values[index++];
                }
            }
        }

        /// <summary>
        /// Combines operands from both arguments.
        /// </summary>
        public static Operands operator +(Operands ops1, Operands ops2)
        {
            if (ops1 == null)
            {
                return ops2?.Clone() ?? new Operands();
            }

            var cloned = ops1.Clone();

            if (ops2 == null)
            {
                return cloned;
            }

            cloned.Combine(ops2);

            return cloned;
        }

        public IEnumerator<char> GetEnumerator()
        {
            for (int i = 0; i < OPCOUNT; ++i)
            {
                if (_operands[i] != null)
                {
                    yield return (char)(i + 'a');
                }
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
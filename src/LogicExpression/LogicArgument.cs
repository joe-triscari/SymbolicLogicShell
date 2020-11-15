using System;
using System.Collections.Generic;

namespace LogicExpression
{
    public class LogicArgument
    {
        private readonly List<LogicExpression> _premises = new List<LogicExpression>();
        private LogicExpression _conclusion;

        public void AddPremise(LogicExpression premise)
        {
            _premises.Add(premise);
        }

        public void SetConclusion(LogicExpression conclusion)
        {
            _conclusion = conclusion;
        }

        public bool IsValid()
        {
            var expression = LogicExpression.Create(ToExpression());
            return expression.IsTautology();
        }

        public string ToExpression()
        {
            if (_premises.Count == 0)
                throw new Exception("Cannot convert LogicArgument to String because no premises have been added.");

            if (_conclusion == null)
                throw new Exception("Cannot convert LogicArgument to String because no conclusion has been set.");

            string sAnt = string.Empty;
            for (int i = 0; i < _premises.Count; ++i)
            {
                if (i == 0)
                    sAnt = _premises[i].ToString();
                else
                    sAnt = "(" + sAnt + "&" + _premises[i] + ")";
            }

            return "(" + sAnt + ">" + _conclusion + ")";
        }
    }
}
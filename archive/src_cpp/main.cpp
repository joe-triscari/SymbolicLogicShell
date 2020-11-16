#include "LogicExpressionFactory.h"
#include <iostream>
#include <fstream>

bool IsPrime(int n)
{
	if(n ==2) return true;
	if(n < 2 || (n &1)==0) return false;

	int s = (int)floor(sqrt((double)n));
	for(int i=2; i <= s; i++)
		if(n % i == 0) return false;

	return true;
}

int main2()
{
	std::ofstream out("i:\\prime.lis");
	for(int i=1; i<=200; i++)
	{
		if(IsPrime(i))
		{
			out << i << "\t*" << std::endl;
		}
		else
		{
			out << i << std::endl;
		}
	}
	return 0;
}
// Todo:
// 1) Add ref counter on parse tree.

using namespace Logic;

char all[] = "(a&(b&(c&(d&(e&(f&(g&(h&(i&(j&(k&(l&(m&(n&(o&(p&(q&(r&(s&(t&(u&(v&(w&(x&(y&z)))))))))))))))))))))))))";
int main()
{
	bool b;

	try
	{

		LogicExpression e(all);
		b = e.GetTruthValue();
//		b =e.IsContingency();

		LogicExpression e1("(p>q)"), e2("(r>s)"), e3("(p&r)");
		LogicExpression c("(q&s)"), e4("p"), e5("q"), e6("(p|q)");
		std::string str;

		b = e1.IsContingency();

		e1.GetOperands()->SetValueOf('p', false);
		e1.GetOperands()->SetValueOf('q', false); 
		b = e1.GetTruthValue();

		b = false;
		b = ((e1 & e2 & e3) > c);//&& ((e4 | e5) == e6);

		LogicArgument arg;

		arg.AddPremise(e1);
		arg.AddPremise(e2);
		arg.AddPremise(e3);
		arg.Conclusion = c;

		LogicExpression ee = arg.Expression;

		b = arg.IsValid();
		
		e4 = !e1;
	}
	catch(const LogicException& e)
	{
		std::string msg = e.GetMessage();
		std::cerr << msg.c_str() << std::endl;
	}
		
	return 0;
}
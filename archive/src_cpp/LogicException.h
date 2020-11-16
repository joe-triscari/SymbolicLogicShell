#ifndef __LogicException_h__
#define __LogicException_h__

namespace Logic
{

	class LogicException : public std::exception
	{
	public:
		LogicException() = default;

		LogicException(const std::string& msg)
		{
			SetMessage(msg);
		}

		std::string GetMessage() const
		{
			return _message;
		}

		void SetMessage(const std::string& msg)
		{
			_message = msg;
		}

	private:
		std::string _message;
	};

}

#endif
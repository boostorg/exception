//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef UUID_D63C9FFE03C611E7B6F710AB63EDCBF1
#define UUID_D63C9FFE03C611E7B6F710AB63EDCBF1

namespace
boost
	{
	class
	exception_datum
		{
		exception_datum( exception_datum const & );
		exception_datum & operator=( exception_datum const & );
		std::type_info ti_;
		shared_ptr<void> v_;
		public:
		explicit
		template <class T>
		exception_datum( T const & v ):
			ti_(typeid(T)),
			v_(make_shared<T>(v))
			{
			}
		template <class T>
		T *
		cast()
			{
			if( typeid(T)==ti_ )
				return static_cast<T *>(v_.get());
			else
				return 0;
			}
		};
	class
	exception_data
		{
		std::map<std::string,exception_datum> data_;
		protected:
		exception_data()
			{
			}
		~exception_data()
			{
			}
		public:
		template <class T>
		exception_data &
		set( char const * tag, T const & value )
			{
			data_[tag]=exception_datum(value);
			return *this;
			}
		template <class T>
		T const *
		get( char const * tag ) const
			{
			auto it=data_.find(tag);
			if( it!=data_.end() )
				return it->cast<T>();
			else
				return 0;
			}
		};
	}

catch(
exception_data & d )
	{
	d["file_name"].set<std::string>("foo.txt");
	d["file_name"].get<std::string>();

	d.set<std::string>("file_name","foo.txt");
	throw;
	}

throw_exception(foo_error(),make_pair<std::string,int>("errno",errno),pair<std::string,float>("width",width));

#endif

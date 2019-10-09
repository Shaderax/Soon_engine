#pragma once

// Not mine 
namespace Soon
{
	template <typename T>
		struct TypeWrapper<const T>
		{
			typedef T TYPE;
			typedef const T CONSTTYPE;
			typedef T& REFTYPE;
			typedef const T& CONSTREFTYPE;
		};

	template <typename T>
		struct TypeWrapper<const T&>
		{
			typedef T TYPE;
			typedef const T CONSTTYPE;
			typedef T& REFTYPE;
			typedef const T& CONSTREFTYPE;
		};

	template <typename T>
		struct TypeWrapper<T&>
		{
			typedef T TYPE;
			typedef const T CONSTTYPE;
			typedef T& REFTYPE;
			typedef const T& CONSTREFTYPE;
		};

	class Variant
	{
		public:
			Variant() { }

			template<class T>
				Variant(T inValue) :
					mImpl(new VariantImpl<typename TypeWrapper<T>::TYPE>(inValue))
				{
				}

			template<class T>
				typename TypeWrapper<T>::REFTYPE getValue()
				{
					return dynamic_cast<VariantImpl<typename TypeWrapper<T>::TYPE>&>(*mImpl).mValue;
				}

			template<class T>
				typename TypeWrapper<T>::CONSTREFTYPE getValue() const
				{
					return dynamic_cast<VariantImpl<typename TypeWrapper<T>::TYPE>&>(*mImpl).mValue;
				}

			template<class T>
				void setValue(typename TypeWrapper<T>::CONSTREFTYPE inValue)
				{
					mImpl = new VariantImpl<typename TypeWrapper<T>::TYPE>(inValue);
				}

		private:
			struct AbstractVariantImpl
			{
				virtual ~AbstractVariantImpl() {}
			};

			template<class T>
				struct VariantImpl : public AbstractVariantImpl
			{
				VariantImpl(T inValue) : mValue(inValue) { }

				~VariantImpl() {}

				T mValue;
			};

			AbstractVariantImpl* mImpl;
	};
}

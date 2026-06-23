#pragma once

struct Property
{
    Property(const char* n, unsigned long long s)
		: name(n), size(s)
    {
    }

	const char* name;
	unsigned long long size;

    virtual void* Get(void* object) const = 0;

    template<typename T>
    const T& Get(void* object) const;


    virtual void Set(void* object, void* value) const = 0;

	template<typename T>
    void Set(void* object, const T& value) const;
};

template<typename T>
inline const T& Property::Get(void* object) const
{
    return *reinterpret_cast<T*>(Get(object));
}

template<typename T>
inline void Property::Set(void* object, const T& value) const
{
    Set(object, (void*)&value);
}


template<typename Class, typename Member>
struct TypedProperty : Property
{
    Member Class::* member;

    TypedProperty(const char* n, unsigned long long s, Member Class::* m)
        : Property(n, s), member(m)
    {
    }

    void* Get(void* object) const override
    {
        auto* obj = static_cast<Class*>(object);
        return &(obj->*member);
    }

	void Set(void* object, void* value) const override
	{
		auto* obj = static_cast<Class*>(object);
		auto* val = static_cast<Member*>(value);
		obj->*member = *val;
	}
};






struct ClassInfoBase
{
	virtual const char* GetName() const = 0;
	virtual const Property* const* GetProperties() const = 0;
	virtual unsigned long long GetPropertyCount() const = 0;

    const Property* GetProperty(const char* propertyName) const;

	virtual ~ClassInfoBase() = default;
};

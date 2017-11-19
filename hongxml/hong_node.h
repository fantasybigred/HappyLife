#pragma once
#include <string>

class hong_attr
{
public:
	hong_attr() :m_attr_name(""), m_next(nullptr) {}
	hong_attr(std::string name, std::string val) :m_attr_name(name), m_attr_val(val), m_next(nullptr) {}
	hong_attr(std::string name, std::string val, hong_attr* next) :m_attr_name(name), m_attr_val(val), m_next(next) {}
	std::string get_attr_name()
	{
		return m_attr_name;
	}
	void set_attr_name(std::string name)
	{
		 m_attr_name = name;
	}
	std::string get_attr_val()
	{
		return m_attr_val;
	}
	void set_attr_val(std::string val)
	{
		m_attr_val = val;
	}
	hong_attr* next()
	{
		return m_next;
	}
	void set_next(hong_attr* next)
	{
		m_next = next;
	}
private:
	std::string m_attr_name;
	std::string m_attr_val;
	hong_attr* m_next;
};

class hong_node
{
public:
	hong_node() :m_tag_name(""), m_text(""), m_attr(NULL), m_next(NULL), m_child(NULL) {}
	hong_node(std::string name, std::string text) :m_tag_name(name), m_text(text), m_attr(NULL), m_next(NULL), m_child(NULL) {}
	std::string get_tag_name()
	{
		return m_tag_name;
	}
	void set_tag_name(std::string name)
	{
		m_tag_name = name;
	}
	std::string get_tag_text()
	{
		return m_text;
	}
	void set_tag_text(std::string text)
	{
		m_text = text;
	}

public:
	hong_attr* get_attr()
	{
		return m_attr;
	}
	void add_attr(hong_attr* attr)
	{
		if (m_attr = NULL)
		{
			m_attr = attr;
		}
		hong_attr* tmpattr = m_attr;
		while (tmpattr->next())
		{
			tmpattr = tmpattr->next();
		}
		tmpattr->set_next(attr);
	}

	hong_node* next()
	{
		return m_next;
	}
	void add_next(hong_node* node)
	{
		if (m_next = NULL)
		{
			m_next = node;
		}
		hong_node* tmpndoe = m_next;
		while (tmpndoe->next())
		{
			tmpndoe = tmpndoe->next();
		}
		tmpndoe->m_next = node;
	}

	hong_node* child()
	{
		return m_child;
	}
	void add_child(hong_node* node)
	{
		if (m_child = NULL)
		{
			m_child = node;
		}
		hong_node* tmpchild = m_child;
		while (tmpchild->child())
		{
			tmpchild = tmpchild->child();
		}
		tmpchild->m_child= node;
	}

private:
	std::string m_tag_name;
	std::string m_text;
	hong_attr* m_attr;
	hong_node* m_next;
	hong_node* m_child;
};
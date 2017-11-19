#include "load_xml.h"
#include <stack>

bool hongxml::load_xml(const string & file_path)
{
	fstream fs(file_path);
	stringstream buffer;
	buffer << fs.rdbuf();
	string content(buffer.str());
	cout << content << endl;

	vector<string> nodes;
	convert_xml_to_nodes(content, nodes);

	for (auto x : nodes)
	{
		cout << x << endl;
	}

	return false;
}

bool hongxml::parse(const string & content, hong_node* cur_node)
{
	if(content.size()==0)
		return false;
	size_t left = content.find('<');
	if (left == string::npos)
		return false;
	size_t right = content.find('>');
	if (right == string::npos)
		return false;
	if (left >= right)
		return false;
	string node_content;
}

bool hongxml::convert_xml_to_nodes(const string & content, vector<string>& nodes)
{
	string tmpnode = "";
	bool flag = false;
	for (size_t i = 0; i < content.size(); ++i)
	{
		if (content[i] == '<')
		{
			flag = true;
			tmpnode += content[i];
			continue;
		}
		if (content[i] == '>')
		{
			tmpnode += content[i];
			flag = false;
			nodes.push_back(tmpnode);
			tmpnode = "";
			continue;
		}
		if (flag)
		{
			tmpnode += content[i];
			continue;
		}
	}
	return true;
}

bool convert_xml_to_nodes(const string & content)
{
	int layer = 0;
	stack<char> st;
	char pre_ch = 0;
	for (size_t i = 0; i < content.size(); ++i)
	{
		if ((content[i] == '/'&&pre_ch == '<'))
		{
			string node_text = "";
			string node_head = "";
			bool flag = true;
			while (st.top() != '<')
			{
				if (st.top() == '>')
				{
					st.pop();
					flag = false;
					continue;
				}
				if (flag&&st.top() != '>')
				{
					node_text += st.top();
					st.pop();
					continue;
				}
				node_head += st.top();
				st.pop();
			}
			hong_node* tmpnode = new hong_node();

		}
		if (content[i] == '>' && pre_ch == '/')
		{

		}
		if (content[i] == '<')
		{
			st.push(content[i]);
		}
	}
	return false;
}

int main()
{
	hongxml xml;
	xml.load_xml("user_info.xml");
	system("PAUSE");
	return 0;
}

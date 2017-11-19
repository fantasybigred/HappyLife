#pragma once

#include "hong_node.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class hongxml
{
public:
	bool load_xml(const string& file_path);
	bool parse(const string& content, hong_node* cur_node);
	bool convert_xml_to_nodes(const string & content, vector<string>& nodes);
private:
	hong_node* m_root;
};
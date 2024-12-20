#include "Location.h"

Location::Location(std::string filename) : _autoindex(FALSE), _filename(filename)
{
	_counterView["root"] = 0;
	_counterView["alias"] = 0;
	_counterView["allowedMethods"] = 0;
	_counterView["autoindex"] = 0;
	_counterView["upload_path"] = 0;
}

Location::Location(const Location &other)
{
	*this = other;
}

Location::~Location()
{
}

Location &Location::operator=(const Location &other)
{
	if (this != &other)
	{
		_path = other._path;
		_root = other._root;
		_rewrite = other._rewrite;
		_alias = other._alias;
		_index = other._index;
		_allowedMethods = other._allowedMethods;
		_autoindex = other._autoindex;
		_cgiExtension = other._cgiExtension;
		_uploadPath = other._uploadPath;
		_counterView = other._counterView;
		_filename = other._filename;
	}
	return (*this);
}

void Location::addAllowedMethods(std::vector<std::string> &tokens)
{
	Methods met;

	incrementCounter("allowedMethods");
	for (size_t i = 1; i < tokens.size(); i++)
    {
		std::string token = tokens[i];
		if (ConfigParser::isMethodSupported(token) == false)
			Logger::log(FATAL, "Invalid method: \"%s\" in file: %s:%d", token.c_str(), _filename.c_str(), ConfigParser::countLineFile);
		if (token == "GET")
			met = GET;
		else if (token == "POST")
			met = POST;
		else if (token == "DELETE")
			met = DELETE;
		else if (token == "PUT")
			met = PUT;
		else
			Logger::log(FATAL, "Invalid method: \"%s\" in file: %s:%d", token.c_str(), _filename.c_str(), ConfigParser::countLineFile);
		if (std::find(_allowedMethods.begin(), _allowedMethods.end(), met) != _allowedMethods.end())
			Logger::log(FATAL, "Duplicate method: \"%s\" in file: %s:%d", token.c_str(), _filename.c_str(), ConfigParser::countLineFile);
		_allowedMethods.push_back(met);
	}
}

Mode Location::strToBool(std::string &str)
{
	if (str == "on")
		return (TRUE);
	else if (str == "off")
		return (FALSE);
	else
		Logger::log(FATAL, "Invalid value for autoindex: \"%s\" in file: %s:%d", str.c_str(), _filename.c_str(), ConfigParser::countLineFile);
	return (FALSE);
}

void Location::addIndexes(std::vector<std::string> &token)
{
	for (size_t i = 1; i < token.size(); i++)
	{
		if (std::find(_index.begin(), _index.end(), token[i]) == _index.end())
			_index.push_back(token[i]);
	}
}

void Location::addCgiExtension(std::vector<std::string> &token)
{

	if (_cgiExtension.find(token[1]) != _cgiExtension.end())
		Logger::log(FATAL, "Duplicate cgi extension: \"%s\" in file: %s:%d", token[1].c_str(), _filename.c_str(), ConfigParser::countLineFile);
	_cgiExtension[token[1]] = token[2];
}

void Location::setRewrite(std::vector<std::string>& tokens)
{
	int code = std::atoi(tokens[1].c_str());
	if (code < 300 || code > 399)
		Logger::log(FATAL, "Invalid return code: \"%s\" in file: %s:%d", tokens[1].c_str(), _filename.c_str(), ConfigParser::countLineFile);
	_rewrite = std::make_pair(code, tokens[2]);
}

void Location::cleanPaths()
{
	if (_path != "/" && _path[_path.size() - 1] == '/')
		_path.erase(_path.size() - 1);
	
	if (!_root.empty() && _root != "/" && _root[_root.size() - 1] == '/')
		_root.erase(_root.size() - 1);
	
	if (!_alias.empty() && _alias != "/" && _alias[_alias.size() - 1] == '/')
		_alias.erase(_alias.size() - 1);	

	if (!_uploadPath.empty() && _uploadPath != "/" && _uploadPath[_uploadPath.size() - 1] == '/')
		_uploadPath.erase(_uploadPath.size() - 1);

	for (std::map<std::string, std::string>::iterator it = _cgiExtension.begin(); it != _cgiExtension.end(); ++it)
	{
		if (it->second != "/" && it->second[it->second.size() - 1] == '/')
			it->second.erase(it->second.size() - 1);
	}
}

void Location::checkDoubleLine()
{
	std::map<std::string, int>::iterator it;

	for (it = _counterView.begin(); it != _counterView.end(); ++it)
		if (it->second > 1)
			Logger::log(FATAL, "Duplicate line in location context: %s", it->first.c_str());

	if (_counterView["root"] > 0 && _counterView["alias"] > 0)
		Logger::log(FATAL, "Alias and Root can't be set in same location bloc %s", _path.c_str());
}

void Location::setDefaultValues()
{
	if (_allowedMethods.size() == 0)
	{
		_allowedMethods.push_back(GET);
		_allowedMethods.push_back(POST);
		_allowedMethods.push_back(DELETE);
	}
	if (_index.size() == 0)
		_index.push_back("index.html");
}

bool Location::isValidLineLocation(std::vector<std::string> &tokens, std::string &key)
{
	if (tokens.size() < 2)
		return false;
	if (key == "root" && tokens.size() == 2)
		setRoot(tokens[1]);
	else if (key == "autoindex")
		setAutoIndex(strToBool(tokens[1]));
	else if (key == "return" && tokens.size() == 3)
		setRewrite(tokens);
	else if (key == "alias" && tokens.size() == 2)
		setAlias(tokens[1]);
	else if (key == "allow_methods")
		addAllowedMethods(tokens);
	else if (key == "index")
		addIndexes(tokens);
	else if (key == "cgi_extension" && tokens.size() == 3)
		addCgiExtension(tokens);
	else if (key == "upload_path" && tokens.size() == 2)
		setUploadPath(tokens[1]);
	else
		return false;
	return true;
}

Location Location::getLocationConfig(std::ifstream &configFile, std::string &path)
{
	std::string line;
	std::vector<std::string> tokens;
	std::string key;
	bool isCloseLocation = false;

	setPath(path);
	while (std::getline(configFile, line))
	{
		ConfigParser::countLineFile++;
		line = Utils::trimLine(line);
		if (line.empty() || line[0] == '#')
			continue;
		tokens = Utils::split(line, " ");
		key = tokens[0];
		if (key[0] == '}' && key.size() == 1 && tokens.size() == 1)
		{
			isCloseLocation = true;
			break;
		}
		if (isValidLineLocation(tokens, key))
			continue;
		else
			Logger::log(FATAL, "Invalid line: \"%s\" in file: %s:%d", line.c_str(), _filename.c_str(), ConfigParser::countLineFile);
	}
	if (!isCloseLocation && ConfigParser::countLineFile != 0)
		Logger::log(FATAL, "Missing } in file: %s:%d", _filename.c_str(), ConfigParser::countLineFile);
	checkDoubleLine();
	setDefaultValues();
	return (*this);
}

void Location::printPair(const std::string& label, const std::string& value)
{
    std::cout << std::setw(15) << std::left << label << ": " << (value.empty() ? "none" : value) << std::endl;
}

void Location::printBool(const std::string& label, bool value, const std::string& trueStr, const std::string& falseStr)
{
    std::cout << std::setw(15) << std::left << label << ": " << (value ? trueStr : falseStr) << std::endl;
}

void Location::printVector(const std::string& label, const std::vector<std::string>& vec)
{
    std::cout << std::setw(15) << std::left << label << ": " << (vec.empty() ? "none" : "") << std::endl;
    for (std::vector<std::string>::const_iterator it = vec.begin(); it != vec.end(); ++it)
        std::cout << "\t- " << *it << std::endl;
}

void Location::printMap(const std::string& label, const std::map<std::string, std::string>& map)
{
    std::cout << std::setw(15) << std::left << label << ": " << (map.empty() ? "none" : "") << std::endl;
    for (std::map<std::string, std::string>::const_iterator it = map.begin(); it != map.end(); ++it)
        std::cout << "\t- " << it->first << ": " << it->second << std::endl;
}


void Location::printLocation(void)
{
    printPair("Path", _path);
    printPair("Root", _root);
    printPair("Alias", _alias);
    printMap("CGI extension", _cgiExtension);
    printPair("Upload path", _uploadPath);
    printBool("Autoindex", _autoindex == TRUE, "on", "off");

    std::cout << std::setw(15) << std::left << "Rewrite" << ": " 
              << (_rewrite.first != 0 ? Utils::intToString(_rewrite.first) + " " + _rewrite.second : "none") << std::endl;

    printVector("Indexes", _index);

    std::cout << std::setw(15) << std::left << "Allowed methods" << ": " << std::endl;
    for (std::vector<Methods>::const_iterator it = _allowedMethods.begin(); it != _allowedMethods.end(); ++it)
    {
        std::cout << "\t- ";
        if (*it == GET)
            std::cout << "GET";
        else if (*it == POST)
            std::cout << "POST";
        else if (*it == DELETE)
            std::cout << "DELETE";
		else if (*it == PUT)
			std::cout << "PUT";
		else
			std::cout << "UNKNOWN";
        std::cout << std::endl;
    }

}

bool Location::isMethodAllowed(Methods method)
{
	return (std::find(_allowedMethods.begin(), _allowedMethods.end(), method) != _allowedMethods.end());
}

Methods	Location::converStrToMethod(const std::string &method)
{
	if (method == "GET")
		return (GET);
	if (method == "POST")
		return (POST);
	if (method == "DELETE")
		return (DELETE);
	if (method == "PUT")
		return (PUT);
	else 
		return (UNKNOWN);
}
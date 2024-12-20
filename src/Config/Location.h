#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>

#include "Utils.h"
#include "Logger.h"
#include "ConfigParser.h"

enum Methods
{
	GET,
	POST,
	DELETE,
	PUT,
	UNKNOWN
};

enum Mode
{
	FALSE,
	TRUE
};

class Location
{
private:
	std::string                         _path;
	std::string                         _root;
	std::pair<int, std::string>         _rewrite;
	std::string                         _alias;
	std::vector<std::string>            _index;
	std::vector<Methods>                _allowedMethods;
	Mode                                _autoindex;
	std::map<std::string, std::string>  _cgiExtension;
	std::string                         _uploadPath;
	std::map<std::string, int>          _counterView;
	std::string                         _filename;

private:

	bool isValidLineLocation(std::vector<std::string>& tokens, std::string& key);

	void incrementCounter(const std::string& key) { _counterView[key]++; }
	void checkDoubleLine();
	void setDefaultValues();
	Mode strToBool(std::string& str);

	void addAllowedMethods(std::vector<std::string>& tokens);
	void addIndexes(std::vector<std::string>& token);
	void addCgiExtension(std::vector<std::string>& token);

public:
	Location(std::string filename);
	Location(const Location& other);
	~Location();
	Location &operator=(const Location& other);

public:
	Location getLocationConfig(std::ifstream& configFile, std::string& path);

	void setPath(const std::string& path) { _path = path; }
	void setUploadPath(const std::string& uploadPath) { _uploadPath = uploadPath; _counterView["upload_path"]++;}
	void setRoot(const std::string& root) { _root = root;  _counterView["root"]++;}
	void setRewrite(std::vector<std::string>& tokens);
	void setAlias(const std::string& alias) { _alias = alias;  _counterView["alias"]++;}
	void setAutoIndex(Mode autoindex) { _autoindex = autoindex;  _counterView["autoindex"]++;}
	// Getters
	const std::string&                          getPath() const { return _path; }
	const std::string&                          getRoot() const { return _root; }
	const std::pair<int, std::string>&          getRewrite() const { return _rewrite; }
	const std::string&                          getAlias() const { return _alias; }
	const std::vector<std::string>&             getFiles() const { return _index; }
	const std::vector<Methods>&                 getAllowedMethods() const { return _allowedMethods; }
	Mode                                        getAutoIndex() const { return _autoindex; }
	const std::vector<std::string>&             getIndexes() const { return _index; }
	const std::map<std::string, std::string>    &getCGI() const { return _cgiExtension; }
	std::string                                 getCgiPath(const std::string &path) const { return _cgiExtension.at(path); }

	bool    isCgi(const std::string& path) const { return _cgiExtension.find(path) != _cgiExtension.end(); }
	// Print
	void    printLocation(void);
	void    printPair(const std::string& label, const std::string& value);
	void    printBool(const std::string& label, bool value, const std::string& trueStr, const std::string& falseStr);
	void    printVector(const std::string& label, const std::vector<std::string>& vec);
	void    printMap(const std::string& label, const std::map<std::string, std::string>& map);

	static Methods  converStrToMethod(const std::string &method);
	void            cleanPaths();
	bool	        isMethodAllowed(Methods method);
};

#endif
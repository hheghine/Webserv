#include "Utils.hpp"

int my_mkstemp(char *tmpPath) {
    static const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static const int numLetters = sizeof(letters) - 1;
    static const int maxAttempts = 100;
    
    if (!tmpPath) {
        return -1; // Invalid pointer
    }

    std::srand(static_cast<unsigned int>(std::time(0))); // Seed for randomness

    for (int attempt = 0; attempt < maxAttempts; ++attempt) {
        std::stringstream ss;
        ss << "tmp";

        // Generate a random 6-character suffix
        for (int i = 0; i < 6; ++i) {
            ss << letters[std::rand() % numLetters];
        }

        std::strcpy(tmpPath, ss.str().c_str()); // Copy to tmpPath

        std::ofstream file(tmpPath, std::ios::out | std::ios::app);
        if (file) {
            file.close();
            return 1; // Success
        }
    }

    return -1; // Failed to create a unique file
}

/*
** @brief Create a temporary file
**
** @param path : The path of the temporary file
** @param fd : The file descriptor of the temporary file
** @return 0 if success, -1 otherwise
*/
// int	Utils::createTmpFile(std::string &path, int &fd)
// {
// 	// path += "XXXXXX";
// 	path = "/tmp/webserv_XXXXXX";
// 	std::vector<char> tmpPath(path.begin(), path.end());
// 	tmpPath.push_back('\0');

// 	fd = mkstemp(&tmpPath[0]);
// 	if (fd == -1)
// 	{
// 		Logger::log(Logger::ERROR, "[Utils::createTmpFile] Failed to create temporary file");
// 		return (-1);
// 	}
// 	path.assign(tmpPath.begin(), tmpPath.end() - 1);
// 	return (0);
// }

int Utils::createTmpFile(std::string &path, int &fd) {
        static const char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        static const int numLetters = sizeof(letters) - 1;
        // static const int suffixLength = 6;
        static const int maxAttempts = 100;

        path = "/tmp/webserv_XXXXXX";
        std::vector<char> tmpPath(path.begin(), path.end());
        tmpPath.push_back('\0'); // Ensure null termination

        std::srand(static_cast<unsigned int>(std::time(0))); // Seed RNG

        for (int attempt = 0; attempt < maxAttempts; ++attempt) {
            // Generate a random 6-character suffix
            for (size_t i = path.size() - 6; i < path.size(); ++i) {
                tmpPath[i] = letters[std::rand() % numLetters];
            }

            // Try creating the file
            fd = open(&tmpPath[0], O_CREAT | O_EXCL | O_RDWR, 0600);
            if (fd != -1) { // Success
                path.assign(tmpPath.begin(), tmpPath.end() - 1);
                return 0;
            }
        }

        Logger::log(Logger::ERROR, "[Utils::createTmpFile] Failed to create temporary file", "");
        return -1;
    }

/*
** @brief Create a temporary file with a random suffix
**
** @param path : The path of the temporary file
** @param fd : The file descriptor of the temporary file
** @return 0 if success, -1 otherwise
*/
int Utils::createFileRandomSuffix(std::string &path, int &fd)
{
	path += "XXXXXX";
	std::vector<char> tmpPath(path.begin(), path.end());
	tmpPath.push_back('\0');

	fd = my_mkstemp(&tmpPath[0]);
	if (fd == -1)
	{
		Logger::log(Logger::ERROR, "[Utils::createTmpFile] Failed to create temporary file");
		return (-1);
	}
	path.assign(tmpPath.begin(), tmpPath.end() - 1);
	return (0);
}

/*
** @brief Decode a URL-encoded string
**
** @param str : The URL-encoded string
** @return 0 if success, -1 otherwise
*/
int	Utils::urlDecode(std::string &str)
{
	size_t i = 0;
	while (i < str.size())
	{
		if (str[i] == '%')
		{
			if (i + 2 >= str.size())
				return (-1);
			char c = hexToChar(str[i + 1]) * 16 + hexToChar(str[i + 2]);
			str[i] = c;
			str.erase(i + 1, 2);
		}
		i++;
	}
	return (0);
}

/*
** @brief Convert a hexadecimal character to a char
**
** @param c : The hexadecimal character
** @return The char
*/
char	Utils::hexToChar(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	return (0);
}

/*
** @brief Convert a string to an unsigned long long
**
** @param clientMaxBodySize : The string to convert
** @return The unsigned long long
*/
unsigned long long Utils::strToUll(std::string clientMaxBodySize){
	unsigned long long size = BS_DEFAULT_CLIENT_MAX_BODY_SIZE;
	
	std::stringstream ss(clientMaxBodySize); // Use std::stringstream instead of stringstream
	ss >> size;

	if (ss.fail() || !ss.eof())
	{
		return (BS_DEFAULT_CLIENT_MAX_BODY_SIZE);
	}
	return (size);
}

/*
** @brief Convert an unsigned long long to a string
**
** @param ull : The unsigned long long to convert
** @return The string
*/
std::string Utils::ullToStr(unsigned long long ull){
	std::ostringstream oss;
	oss << ull;
	return (oss.str());
}





/* UTILS */

void printMsg(std::ostream &os, const char *msg, ...)
{
	const int initialBufferSize = 1024;
	std::vector<char> buffer(initialBufferSize);

	std::va_list args;
	va_start(args, msg);
	int size = std::vsnprintf(buffer.data(), initialBufferSize, msg, args);
	va_end(args);

	// Handling error
	if (size < 0)
	{
		return;
	}

	// Resize the buffer if needed
	while (size >= static_cast<int>(buffer.size()))
	{
		buffer.resize(buffer.size() * 2);
		va_start(args, msg);
		size = std::vsnprintf(buffer.data(), buffer.size(), msg, args);
		va_end(args);
	}

	os << buffer.data() << std::endl;
}



/**
 * @brief renvoie true si le dossier existe
 */
bool directoryExist(const char *path)
{
	struct stat info;
	if (stat(path, &info) != 0)
	{
		return false;
	}
	return (info.st_mode & S_IFDIR) != 0;
}

/**
 * @brief renvoie true si le fichier existe
 */
bool fileExist(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0 && S_ISREG(buffer.st_mode));
}

/**
 * @brief take string and return trimed line
 * 	example:
 * 		 string => "   bonjour   "
 * 		return : "bonjour"
 * @param line
 * @return std::string
 */
std::string trimLine(std::string &line)
{
	const std::string white_chars = " \t\n\r\f\v";
	std::string result;

	int start = 0;
	while (white_chars.find(line[start]) != std::string::npos)
		start++;
	int end = line.size() - 1;
	while (end >= 0 && white_chars.find(line[end]) != std::string::npos)
		end--;

	for (int i = start; i <= end; i++)
		result.push_back(line[i]);

	return (result);
}

/**
 * @brief Splits a string into multiple substrings based on a delimiter.
 *
 * @example
 * std::string input = "Hello,World,!";
 * std::string delimiter = ",";
 * // result will contain {"Hello", "World", "!"}
 */
std::vector<std::string> split(std::string s, std::string delimiter)
{
	size_t pos = 0;
	std::string token;
	std::vector<std::string> result;
	s = trimLine(s);
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		result.push_back(token);
		s.erase(0, pos + delimiter.length());
		s = trimLine(s);
	}
	result.push_back(s);
	return (result);
}

std::string unsignedIntToString(unsigned int value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

std::string intToString(int value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

/**
 * @brief Protected call to a function
 * @param ret return code of function to test
 * @param msg message in case of error
 * @param isFatal if true, the error is fatal (optional, default is true)
 * @return the return code of the function if >= 0
 */
int protectedCall(int ret, std::string msg, bool isFatal)
{
	if (ret < 0)
	{
		if (isFatal)
			Logger::log(Logger::FATAL, msg.c_str());
		else
			Logger::log(Logger::ERROR, msg.c_str());
	}
	return ret;
}


std::string		extractIp(std::string ipPort)
{
	return(ipPort.substr(0, ipPort.find(":")));
}

unsigned int	extractPort(std::string ipPort)
{
	return(std::atoi(ipPort.substr(ipPort.find(":") + 1).c_str()));
}
	
/**
 * @brief renvoie true si le fichier est vide
 */
bool isEmptyFile(){
	return (ConfigParser::countLineFile == 0);
}


std::string intToHexa(ssize_t num) {
    std::stringstream stream;
    stream << std::hex << num;
    return stream.str();
}

/**
 * @brief get the extension of a file
 */
std::string getExtension(const std::string &path, bool includeDot)
{
	std::string ext;
	std::string::size_type idx = path.rfind('.');
	if (idx != std::string::npos)
	{
		if (includeDot)
			ext = path.substr(idx);
		else
			ext = path.substr(idx + 1);
	}
	if ((includeDot && ext.size() <= 1) || (!includeDot && ext.empty()))
		return "";
	if (ext.find('/') != std::string::npos)
		return "";
	return ext;
}


// _____________________________ MODIFY EPOLL _____________________________
/**
 * WARNING: this function do not update flags for a socket, it only add socket to 
 * epoll with flags
 */
void addSocketEpoll(int epollFD, int sockFD, uint32_t flags)
{
	epoll_event ev;
	ev.events = flags;
	ev.data.fd = sockFD;
	protectedCall(epoll_ctl(epollFD, EPOLL_CTL_ADD, sockFD, &ev), "Error with epoll_ctl function", false);
}

/**
 * @brief
 * WARNING: this function over written previous flags
 * 
 */
void modifySocketEpoll(int epollFD, int sockFD, uint32_t flags)
{
	epoll_event ev;
	ev.events = flags;
	ev.data.fd = sockFD;
	protectedCall(epoll_ctl(epollFD, EPOLL_CTL_MOD, sockFD, &ev), "Error with epoll_ctl function", false);
}

void deleteSocketEpoll(int epollFD, int sockFD)
{
	epoll_event ev;
	ev.data.fd = sockFD;
	protectedCall(epoll_ctl(epollFD, EPOLL_CTL_DEL, sockFD, &ev), "Error with epoll_ctl function", false);
}

std::string getErrorMessage(int code)
{
	switch (code)
	{
		// 2xx Success
		case 200:
			return "OK";
		case 201:
			return "Created";
		case 202:
			return "Accepted";
		case 204:
			return "No Content";
		
		// 3xx Redirection
		case 301:
			return "Moved Permanently";
		case 302:
			return "Found";
		case 303:
			return "See Other";
		case 304:
			return "Not Modified";
		case 307:
			return "Temporary Redirect";
		case 308:
			return "Permanent Redirect";
		
		// 4xx Client Errors
		case 400:
			return "Bad Request";
		case 401:
			return "Unauthorized";
		case 403:
			return "Forbidden";
		case 404:
			return "Not Found";
		case 405:
			return "Not Allowed";
		case 408:
			return "Request Timeout";
		case 409:
			return "Conflict";
		case 410:
			return "Gone";
		case 413:
			return "Payload Too Large";
		case 414:
			return "URI Too Long";
		case 415:
			return "Unsupported Media Type";
		case 429:
			return "Too Many Requests";

		// 5xx Server Errors
		case 500:
			return "Internal Server Error";
		case 501:
			return "Not Implemented";
		case 502:
			return "Bad Gateway";
		case 503:
			return "Service Unavailable";
		case 504:
			return "Gateway Timeout";
		case 505:
			return "HTTP Version Not Supported";
		
		default:
			return "Unknown Error";
	}
}


/**
 * @brief Fonction pour obtenir le type MIME basé sur l'extension de fichier
 */
std::string getMimeType(const std::string &path)
{
	std::map<std::string, std::string> mimeTypes;

	mimeTypes[".html"] = "text/html";
	mimeTypes[".htm"] = "text/html";
	mimeTypes[".css"] = "text/css";
	mimeTypes[".js"] = "application/javascript";
	mimeTypes[".jpg"] = "image/jpeg";
	mimeTypes[".jpeg"] = "image/jpeg";
	mimeTypes[".png"] = "image/png";
	mimeTypes[".gif"] = "image/gif";
	mimeTypes[".svg"] = "image/svg+xml";
	mimeTypes[".json"] = "application/json";
	mimeTypes[".txt"] = "text/plain";
	mimeTypes[".pdf"] = "application/pdf";
	mimeTypes[".zip"] = "application/zip";
	mimeTypes[".tar"] = "application/x-tar";
	mimeTypes[".gz"] = "application/gzip";
	mimeTypes[".mp3"] = "audio/mpeg";
	mimeTypes[".mp4"] = "video/mp4";
	mimeTypes[".avi"] = "video/x-msvideo";
	mimeTypes[".mpeg"] = "video/mpeg";
	mimeTypes[".webm"] = "video/webm";
	mimeTypes[".ogg"] = "video/ogg";
	mimeTypes[".ico"] = "image/x-icon";
	mimeTypes[".webp"] = "image/webp";
	mimeTypes[".woff"] = "font/woff";
	mimeTypes[".woff2"] = "font/woff2";
	mimeTypes[".ttf"] = "font/ttf";
	mimeTypes[".otf"] = "font/otf";
	mimeTypes[".eot"] = "application/vnd.ms-fontobject";
	mimeTypes[".csv"] = "text/csv";
	mimeTypes[".xml"] = "application/xml";
	mimeTypes[".xhtml"] = "application/xhtml+xml";
	mimeTypes[".webmanifest"] = "application/manifest+json";
	mimeTypes[".ico"] = "image/x-icon";
	mimeTypes[".mkv"] = "video/x-matroska";

	std::string::size_type idx = path.rfind('.');
	if (idx != std::string::npos)
	{
		std::string ext = path.substr(idx);
		if (mimeTypes.find(ext) != mimeTypes.end())
		{
			return mimeTypes[ext];
		}
	}
	return "application/octet-stream";
}


// _____________________________ LIST DIRECTORY _____________________________



/**
 * @brief build the html page with the files in the directory
 */
std::string buildPage(std::vector<std::string> files, std::string path, std::string root){
    std::string page;
    std::string header = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Listing Directory</title><style>@import url('https://fonts.googleapis.com/css2?family=Inter:ital,opsz,wght@0,14..32,100..900;1,14..32,100..900&display=swap');body{padding: 0;margin: 0;box-sizing: border-box;font-family: 'Inter', sans-serif;background-color: #0a0a0a;color: #fff;text-align: center;display: flex;justify-content: center;align-items: center;height: 100vh;background-image: url('https://www.transparenttextures.com/patterns/starry-night.png');background-size: cover;background-attachment: fixed;overflow: hidden;}h1{font-size: 3rem;color: #ff4b5c;text-shadow: 0 0 15px rgba(255, 75, 92, 0.7);margin-bottom: 2rem;}a{color: white;text-decoration: none;background-color: #121212;padding: 10px 20px;margin: 10px;border-radius: 10px;box-shadow: 0 0 15px rgba(0, 255, 153, 0.6);transition: transform 0.3s ease;}a:hover{opacity: 0.9;transform: scale(1.05);}ul{list-style-type: none;padding: 0;display: flex;flex-direction: column;align-items: center;}ul li{margin: 5px 0;width: 100%;display: flex;justify-content: center;}div.container{background-color: rgba(0, 0, 0, 0.7);padding: 2rem;border-radius: 15px;width: 90%;max-width: 800px;box-shadow: 0 0 25px rgba(255, 75, 92, 0.7);}</style></head>";
    std::string body = "<body><div class=\"container\"><h1>Index of " + path.substr(root.size()) + "</h1><ul>";
    
    // Add links to the body
    for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); ++it)
    {
        body += "<li><a href=\"";
        body += *it;
        body += "\">";
        body += *it;
        body += "</a></li>";
    }
    body += "</ul></div></body></html>";
    
    return header + body;
}




/**
 * @brief fonction qui clean le path
 * ex: /Users/toukoum/42/webserv/././www/../www/../
 * -> /Users/toukoum/42/webserv/
 */
void cleanPath(std::string& path){
	 if (path[0] != '/')
        path.insert(0, "/");

    if (path[path.size() - 1] != '/')
        path += "/";

    // Remove all "/./" occurrences
    size_t pos;
    while ((pos = path.find("/./")) != std::string::npos) {
        path.erase(pos, 2); // Supprime le "/." (2 caractères)
    }

		// delete all /prev/../
		while ((pos = path.find("/../")) != std::string::npos){
			if (pos == 0){
				path.erase(0, 3);
				continue;
			}
			size_t prev = path.rfind('/', pos - 1);
			if (prev != std::string::npos){
				path.erase(prev, pos - prev + 3);
			}else{
				path.erase(0, pos + 3);
			}
		}
}

/**
 * @brief fonction qui check si le path demande est un fichier ou un dossier 
 * a l'interieur du dossier root
 * condition:
 * 	root = /42/
 * 	path = /42/toukoum
 * 
 * 
 * @return int 
 */
bool is_path_within_root(const std::string& root, std::string& path) {
		size_t i = 0;
		while (i < root.size() && i < path.size())
		{
			if (root[i] != path[i])
				break;
			i++;
		}
		return (i == root.size());
}


/**
 * @brief List all files in a directory
 * @param path path of the directory
 * 
 */
std::string listDirectory(std::string path, std::string root){

	cleanPath(path);
	if (path[0] != '.')
		path.insert(0, ".");
	Logger::log(Logger::DEBUG, "Root: %s", root.c_str());
	Logger::log(Logger::DEBUG, "Path: %s", path.c_str());

	if (!is_path_within_root(root, path)) {
		Logger::log(Logger::ERROR, "Path asked is not within root");
		return ErrorPage::getPage(403);
	}

	std::vector<std::string> files;
	DIR *dir = opendir(path.c_str());
	if (dir == NULL){
		Logger::log(Logger::ERROR, "Failed to open directory: %s", path.c_str());
		return ErrorPage::getPage(404);
	}
	struct dirent *ent;
	while ((ent = readdir(dir)) != NULL)
	{
		files.push_back(ent->d_name);
	}
	closedir(dir);

	std::string body = buildPage(files, path, root);
	std::string header = "HTTP/1.1 200 OK\r\n";
	header += "Content-Type: text/html\r\n";
	header += "Content-Length: " + intToString(body.size()) + "\r\n";
	header += "\r\n";
	return header + body;
}


std::string uint64ToString(u_int64_t value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

std::string convertToLowercase(const std::string& str) {
    std::string lowercaseStr = str;
    std::transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(), ::tolower);
    return lowercaseStr;
}


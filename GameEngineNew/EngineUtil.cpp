//-------------------------------------------------------------------------//
// MyUtil.h
// Some utility stuff - file reading and such
//
// David Cline
// 6/14/2014
//-------------------------------------------------------------------------//

// Local includes
#include "EngineUtil.h"

//-------------------------------------------------------------------------//
// MISCELLANEOUS
//-------------------------------------------------------------------------//

void ERROR(const string &msg, bool doExit)
{
	cerr << "\nERROR! " << msg << endl;
	if (doExit) exit(0);
}

double TIME(void)
{
	return (double)clock() / (double)CLOCKS_PER_SEC;
}

void SLEEP(int millis)
{
	this_thread::sleep_for(chrono::milliseconds(1));
}

//-------------------------------------------------------------------------//
// OPENGL STUFF
//-------------------------------------------------------------------------//

GLFWwindow* createOpenGLWindow(int width, int height, const char *title, int samplesPerPixel)
{
	// Initialise GLFW
	if (!glfwInit()) ERROR("Failed to initialize GLFW.", true);
	glfwWindowHint(GLFW_SAMPLES, samplesPerPixel);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
	// Open a window and create its OpenGL context
	GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		ERROR("Failed to open GLFW window.", true);
	}
	glfwMakeContextCurrent(window);
    
	// Ensure we can capture the escape key being pressed
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		ERROR("Failed to initialize GLEW.", true);
	}
    
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
    
	// Print the OpenGL version we are working with
	char *GL_version = (char *)glGetString(GL_VERSION);
	printf("OpenGL Version: %s\n", GL_version);
	return window;
}

//-------------------------------------------------------------------------//

GLuint loadShader(const string &fileName, GLuint shaderType)
{
	// load the shader as a file
	string mainCode;
	if (!loadFileAsString(fileName, mainCode)) {
		ERROR("Could not load file '" + fileName + "'", false);
		return NULL_HANDLE;
	}
    
	string shaderCode;
	string alreadyIncluded = fileName;
	replaceIncludes(mainCode, shaderCode, "#include", alreadyIncluded, true);
    
    
	// print the shader code
#ifdef _DEBUG
	cout << "\n----------------------------------------------- SHADER CODE:\n";
	cout << shaderCode << endl;
	cout << "--------------------------------------------------------------\n";
#endif
    
	// transfer shader code to card and compile
	GLuint shaderHandle = glCreateShader(shaderType); // create handle for the shader
	const char* source = shaderCode.c_str();          // get C style string for shader code
	glShaderSource(shaderHandle, 1, &source, NULL);   // pass the shader code to the card
	glCompileShader(shaderHandle);                    // attempt to compile the shader
	
	// check to see if compilation worked
	// If the compilation did not work, print an error message and return NULL handle
	int status;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		ERROR("compiling shader '" + fileName + "'", false);
		GLint msgLength = 0;
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &msgLength);
		std::vector<char> msg(msgLength);
		glGetShaderInfoLog(shaderHandle, msgLength, &msgLength, &msg[0]);
		printf("%s\n", &msg[0]);
		glDeleteShader(shaderHandle);
		return NULL_HANDLE;
	}
    
	return shaderHandle;
}

//-------------------------------------------------------------------------//

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    // Create and link the shader program
    GLuint shaderProgram = glCreateProgram(); // create handle
    if (!shaderProgram) {
        ERROR("could not create the shader program", false);
        return NULL_HANDLE;
    }
    glAttachShader(shaderProgram, vertexShader);    // attach vertex shader
    glAttachShader(shaderProgram, fragmentShader);  // attach fragment shader
    glLinkProgram(shaderProgram);
    
    // check to see if the linking was successful
    int linked;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked); // get link status
    if (!linked) {
        ERROR("could not link the shader program", false);
        GLint msgLength = 0;
        glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &msgLength);
        std::vector<char> msg(msgLength);
        glGetShaderInfoLog(shaderProgram, msgLength, &msgLength, &msg[0]);
        printf("%s\n", &msg[0]);
        glDeleteProgram(shaderProgram);
        return NULL_HANDLE;
    }
    
    // HOOK UP UNIFORM BUFFER AND UNIFORM BLOCK TO SAME BINDING POINT
    GLint lightBlockIndex = glGetUniformBlockIndex(shaderProgram, "Lights");
    glUniformBlockBinding(shaderProgram, lightBlockIndex, LIGHT_BUFFER_ID);
    glBindBufferBase(GL_UNIFORM_BUFFER, LIGHT_BUFFER_ID, gLightBufferObject);
    
    //printf("LIGHT STUFF %d %d %d\n", shaderProgram, lightBlockIndex, lightBufferObject);
    
    return shaderProgram;
    
}

//-------------------------------------------------------------------------//
// GLM UTILITY STUFF
//-------------------------------------------------------------------------//

void printMat(const glm::mat4x4 &m)
{
	printf("\n");
	for (int r = 0; r < 4; r++) {
		printf("[ ");
		for (int c = 0; c < 4; c++) {
			printf("%7.3f ", m[c][r]); // glm uses column major order
		}
		printf("]\n");
	}
}

//-------------------------------------------------------------------------//
// FILE READING
//-------------------------------------------------------------------------//

vector<string> PATH;

void addToPath(const string &p)
{
	PATH.push_back(p);
}

void removeFromPath(const string &p)
{
	for (int i = (int)p.length() - 1; i >= 0; i--) {
		if (PATH[i] == p) PATH.erase(PATH.begin() + i);
	}
}

bool getFullFileName(const string &fileName, string &fullName)
{
	for (int i = -1; i < (int)PATH.size(); i++) {
		if (i < 0) fullName = fileName;
		else fullName = PATH[i] + fileName;
        
		FILE *f = fopen(fullName.c_str(), "rb");
		if (f != NULL) {
			fclose(f);
			return true;
		}
	}
	fullName = "";
	return false;
}

FILE *openFileForReading(const string &fileName)
{
	string fullName;
	bool fileExists = getFullFileName(fileName, fullName);
	if (fileExists) {
		cout << "Opening file '" << fileName << "'" << endl;
		return fopen(fullName.c_str(), "rb");
	}
    
	string msg = "Could not open file " + fileName;
	ERROR(msg.c_str(), false);
	return NULL;
}

//-------------------------------------------------------------------------//

bool getToken(FILE *f, string &token, const string &oneCharTokens)
{
	token = "";
	while (!feof(f)) {
		int c = getc(f);
		int tokenLength = (int)token.length();
		int cIsSpace = isspace(c);
		bool cIsOneCharToken = ((int)oneCharTokens.find((char)c) >= 0);
        
		if (cIsSpace && tokenLength == 0) { // spaces before token, ignore
			continue;
		}
		else if (cIsSpace) { // space after token, done
			break;
		}
		else if (c == EOF) { // end of file, done
			break;
		}
		else if ((tokenLength == 0) && cIsOneCharToken) { // oneCharToken, done
			token += (char)c;
			break;
		}
		else if (cIsOneCharToken) { // oneCharToken after another token, push back
			ungetc(c, f);
			break;
		}
		else if ((tokenLength == 0) && (c == '\"' || c == '\'')) { // quoted string, append til end quote found
			char endQuote = c;
			while (!feof(f)) {
				int d = getc(f);
				if (d == endQuote) return true;
				token += (char)d;
			}
			break;
		}
		else if (c == '\"' || c == '\'') { // quote after token started, push back
			ungetc(c, f);
			break;
		}
		else {
			token += (char)c;
		}
	}
	//cout << token << endl;
	return (token.length() > 0);
}

//-------------------------------------------------------------------------//

int getFloats(FILE *f, float *a, int num)
{
	string token;
	int count = 0;
	while (getToken(f, token, "[],")) {
		if (token == "]") {
			break;
		}
		else if (isdigit(token[0]) || token[0] == '-') {
			sscanf(token.c_str(), "%f", &a[count]);
			count++;
			if (count == num) break;
		}
	}
	return count;
}

int getInts(FILE *f, int *a, int num)
{
	string token;
	int count = 0;
	while (getToken(f, token, "[],")) {
		if (token == "]") {
			break;
		}
		else if (isdigit(token[0]) || token[0] == '-') {
			sscanf(token.c_str(), "%d", &a[count]);
			count++;
			if (count == num) break;
		}
	}
	return count;
}
//-------------------------------------------------------------------------//

bool loadFileAsString(const string &fileName, string &fileContents)
{
	printf("loading file '%s'\n", fileName.c_str());
    
	string fullName;
	bool fileExists = getFullFileName(fileName, fullName);
	if (!fileExists) return false;
    
	ifstream fileStream(fullName.c_str());
	if (fileStream.good()) {
		stringstream stringStream;
		stringStream << fileStream.rdbuf();
		fileContents = stringStream.str();
		fileStream.close();
		return true;
	}
	
	fileStream.close();
	return false;
}

//-------------------------------------------------------------------------//

void replaceIncludes(string &src, string &dest, const string &directive,
                     string &alreadyIncluded, bool onlyOnce)
{
	int start = 0;
    
	while (true) {
		int includeIndex = (int)src.find("#include", start);
		if (includeIndex < 0) {
			dest += src.substr(start);
			break;
		}
		if (includeIndex > 0 && !isspace(src[includeIndex - 1])) continue;
		dest += src.substr(start, includeIndex - 1);
		//
		int quoteStart = (int)src.find("\"", start + 8);
		int quoteEnd = (int)src.find("\"", quoteStart + 1);
		start = quoteEnd + 1;
		if (quoteStart >= quoteEnd) {
			ERROR("could not replace includes");
			break;
		}
		string includeFileName = src.substr(quoteStart + 1, (quoteEnd - quoteStart - 1));
		if ((int)alreadyIncluded.find(includeFileName) < 0) {
			if (onlyOnce) {
				alreadyIncluded.append("|");
				alreadyIncluded.append(includeFileName);
			}
			string subSource;
			loadFileAsString(includeFileName, subSource);
			replaceIncludes(subSource, dest, directive, alreadyIncluded, onlyOnce);
		}
	}
}

//-------------------------------------------------------------------------//
// RGBAImage
//-------------------------------------------------------------------------//

RGBAImage::~RGBAImage()
{
	if (textureId != NULL_HANDLE) glDeleteTextures(1, &textureId);
	if (samplerId != NULL_HANDLE) glDeleteSamplers(1, &samplerId);
}

bool RGBAImage::loadPNG(const string &fileName, bool doFlipY)
{
	string fullName;
	getFullFileName(fileName, fullName);
	unsigned error = lodepng::decode(pixels, width, height, fullName.c_str());
	if (error) {
		ERROR(lodepng_error_text(error), false);
		return false;
	}
    
	if (doFlipY) flipY(); // PNGs go top-to-bottom, OpenGL is bottom-to-top
	name = fileName;
	return true;
}

bool RGBAImage::writeToPNG(const string &fileName)
{
	unsigned error = lodepng::encode(fileName.c_str(), pixels, width, height);
	if (error) {
		ERROR(lodepng_error_text(error), false);
		return false;
	}
	return true;
}

void RGBAImage::flipY(void)
{
	unsigned int *a, *b;
	unsigned int temp;
    
	for (int y = 0; y < (int)height / 2; y++)
	{
		a = &pixel(0, y);
		b = &pixel(0, height - 1 - y);
		for (int x = 0; x < (int)width; x++) {
			temp = a[x];
			a[x] = b[x];
			b[x] = temp;
		}
	}
}

void RGBAImage::sendToOpenGL(GLuint magFilter, GLuint minFilter, bool createMipMap)
{
	if (width <= 0 || height <= 0) return;
    
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &pixels[0]);
	if (createMipMap) glGenerateMipmap(GL_TEXTURE_2D);
    
	glGenSamplers(1, &samplerId);
	glBindSampler(textureId, samplerId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
}
//-------------------------------------------------------------------------//

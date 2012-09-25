/*--------------------------------------------------------------------------------------
 Ethanon Engine (C) Copyright 2008-2012 Andre Santee
 http://www.asantee.net/ethanon/

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the
	Software without restriction, including without limitation the rights to use, copy,
	modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
	and to permit persons to whom the Software is furnished to do so, subject to the
	following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
--------------------------------------------------------------------------------------*/

#ifndef ETH_RESOURCE_PROVIDER_H_
#define ETH_RESOURCE_PROVIDER_H_

#include "ETHResourceManager.h"
#include "../Util/ETHGlobalScaleManager.h"
#include "../Platform/ETHPlatform.h"
#include <Platform/Platform.h>
#include <Platform/FileLogger.h>

class ETHShaderManager;

class ETHResourceProvider
{
	static ETHGraphicResourceManagerPtr m_graphicResources;
	static ETHAudioResourceManagerPtr m_audioResources;
	static boost::shared_ptr<ETHShaderManager> m_shaderManager;
	static str_type::string m_programPath, m_resourcePath;
	static VideoPtr m_video;
	static AudioPtr m_audio;
	static InputPtr m_input;
	static Platform::FileLoggerPtr m_logger;
	static ETHGlobalScaleManagerPtr m_globalScaleManager;

public:
	ETHResourceProvider(ETHGraphicResourceManagerPtr graphicResources, ETHAudioResourceManagerPtr audioResources,
				boost::shared_ptr<ETHShaderManager> shaderManager, const str_type::string& resourcePath,
				VideoPtr video, AudioPtr audio, InputPtr input);

	static void Log(const str_type::string& str, const Platform::Logger::TYPE& type);

	ETHGlobalScaleManagerPtr& GetGlobalScaleManager();
	const Platform::FileLogger* GetLogger() const;
	ETHGraphicResourceManagerPtr GetGraphicResourceManager();
	ETHAudioResourceManagerPtr GetAudioResourceManager();
	boost::shared_ptr<ETHShaderManager> GetShaderManager();
	str_type::string GetProgramPath();
	str_type::string GetResourcePath();
	void SetResourcePath(const str_type::string& path);
	const VideoPtr& GetVideo();
	const AudioPtr& GetAudio();
	const InputPtr& GetInput();
	str_type::string GetByteCodeSavePath();
};

typedef boost::shared_ptr<ETHResourceProvider> ETHResourceProviderPtr;

#endif
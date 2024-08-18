#pragma once

namespace btfy
{


	void titlepage()
	{

		// Title Logo
		const char* Title[6]
		{ "                  _          \n",
		"  /\\  /\\__ _  ___| | ___   _ \n",
		" / /_/ / _` |/ __| |/ / | | |\n",
		"/ __  / (_| | (__|   <| |_| |\n",
		"\\/ /_/ \\__,_|\\___|_|\\_\\\\__, |\n",
		"                       |___/ \n",
		};
		const char* Info =
			"Press End to Eject Dll. If you close the window the game will also close\n";




		for (const char* line : Title)
		{
			printf(line);
		}
		printf(Info);

	}


	


}
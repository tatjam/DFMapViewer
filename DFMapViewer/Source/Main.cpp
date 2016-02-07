#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

int main()
{
	
	std::cout << "Welcome to Tatjam's Map Viewer!" << std::endl << std::endl;
	std::cout << "We will first load a file:" << std::endl;
	std::cout << "If you haven't already, export required maps from dwarf fortress" << std::endl;
	std::cout << "Required maps are:" << std::endl;
	std::cout << "- Elevations respecting water level" << std::endl;
	std::cout << "- Biome" << std::endl;
	std::cout << "- Temperature" << std::endl;
	std::cout << "- Rainfall" << std::endl << std::endl;
	std::cout << "Once you have the maps copy them over to the /Resource directory of this program" << std::endl;
	std::cout << "Later rename them to map-[map type], like this: " << std::endl;
	std::cout << "map-elw" << std::endl;
	std::cout << "map-bm" << std::endl;
	std::cout << "map-tmp" << std::endl;
	std::cout << "map-rain" << std::endl;
	std::cout << std::endl;
	std::cout << "Once ready press ENTER!" << std::endl;
	std::cin.get();
	std::cout << "Initializing..." << std::endl;

	int zoomSpeed = 60;
	int sZoomSpeed = 260;
	int aZoomSpeed = 50;

	int moveSpeed = 40;
	int sMoveSpeed = 180;
	int aMoveSpeed = 40;

	int windowX = 512;
	int windowY = 512;

	float spriteZoom = 1;

	bool rescale = false;

	sf::Image map = sf::Image();
	if (map.loadFromFile("Resource/map-elw.bmp") == false)
	{
		std::cout << "Error loading Elevation map (map-elw.bmp)!" << std::endl;
		std::cout << "Make sure you placed the file correctly!" << std::endl;
		std::cout << "Press ENTER to exit!" << std::endl;
		std::cin.get();
		return 0;
	}

	sf::Image tmpMap = sf::Image();
	if (tmpMap.loadFromFile("Resource/map-tmp.bmp") == false)
	{
		std::cout << "Error loading Temperature map (map-tmp.bmp)!" << std::endl;
		std::cout << "Make sure you placed the file correctly!" << std::endl;
		std::cout << "Press ENTER to exit!" << std::endl;
		std::cin.get();
		return 0;
	}

	sf::Image bmMap = sf::Image();
	if (bmMap.loadFromFile("Resource/map-bm.bmp") == false)
	{
		std::cout << "Error loading Biome map (map-bm.bmp)!" << std::endl;
		std::cout << "Make sure you placed the file correctly!" << std::endl;
		std::cout << "Press ENTER to exit!" << std::endl;
		std::cin.get();
		return 0;
	}

	sf::Image rainMap = sf::Image();
	if (rainMap.loadFromFile("Resource/map-rain.bmp") == false)
	{
		std::cout << "Error loading Rainfall map (map-rain.bmp)!" << std::endl;
		std::cout << "Make sure you placed the file correctly!" << std::endl;
		std::cout << "Press ENTER to exit!" << std::endl;
		std::cin.get();
		return 0;
	}

	//Convert the map to our format (pixel by pixel!)

	bool sea = false;
	bool river = false;

	sf::Color riverC(166, 216, 217);
	sf::Color seaC(75, 99, 143);

	sf::Color frozenSeaC(188, 201, 225);
	sf::Color frozenLandC(240, 240, 240);
	sf::Color snowLandC(220, 220, 220);

	//Biomes:

	sf::Color biomeMountain(128, 128, 128);
	sf::Color biomeDesert(255, 192, 0);
	sf::Color biomeHotDesert(255, 176, 0);
	sf::Color biomeScorchingDesert(255, 128, 64);
	sf::Color biomeFlameDesert(255, 96, 32);

	sf::Color biomeDeepJungle(0, 96, 0);
	sf::Color biomeShallowJungle(0, 128, 0);
	sf::Color biomeJungle(0, 160, 0);
	sf::Color biomeLightJungle(0, 192, 32);
	sf::Color biomeSparseJungle(0, 224, 32);

	sf::Color biomeLightTundra(0, 255, 32);
	sf::Color biomeTundra(0, 224, 32);

	sf::Color biomeLake(0, 224, 255);

	sf::Color biomeTropicalSea(0, 0, 255);
	sf::Color biomeSea(0, 128, 255);
	sf::Color biomeArticSea(0, 255, 255);
	sf::Color biomeGlacier(128, 255, 255);


	//--------------------------------------------

	bool mountainB = false;
	bool desert = false;
	bool jungle = false;
	bool forest = false;
	bool tundra = false;
	bool lake = false;
	bool glacier = false;
	bool frozenOcean = false;

	std::cout << "Generating color maps..." << std::endl;

	for (int x = 0; x < map.getSize().x; x++)
	{
		for (int y = 0; y < map.getSize().y; y++)
		{
			mountainB = false;
			desert = false;
			jungle = false;
			forest = false;
			tundra = false;
			lake = false;
			glacier = false;
			frozenOcean = false;

			sf::Color ac = map.getPixel(x, y);
			if (ac.b == 73 && ac.r == 0)
			{
				sea = true;
			}
			else
			{
				sea = false;
			}

			if (ac.r == 0 && !sea)
			{
				river = true;
			}
			else
			{
				river = false;
			}


			if (river == true)
			{
				map.setPixel(x, y, riverC);
			}

			if (sea == true)
			{
				map.setPixel(x, y, seaC);
			}

			//Temperature: (NOT USED FOR NOW)
			//sf::Color tmpC = tmpMap.getPixel(x, y);

			//Get biomes

			sf::Color bC = bmMap.getPixel(x, y);

			if (bC == biomeDesert || bC == biomeHotDesert || bC == biomeScorchingDesert ||
				bC == biomeFlameDesert)
			{
				desert = true;
			}
			else if (bC == biomeDeepJungle || bC == biomeShallowJungle)
			{
				jungle = true;
			}
			else if (bC == biomeSparseJungle || bC == biomeLightJungle || bC == biomeJungle)
			{
				forest = true;
			}
			else if (bC == biomeGlacier)
			{
				glacier = true;
			}
			else if (bC == biomeLake)
			{
				lake = true;
			}
			else if (bC == biomeMountain)
			{
				mountainB = true;
			}
			else if (bC == biomeArticSea)
			{
				frozenOcean = true;
			}

			else
			{
				forest = true;
			}

			//Set elevation for now:
			if (river == false && (sea == false || frozenOcean == true))
			{
				//This is where the fun stuff happens
				//Each biome has diferent elevation values
				if (mountainB == true)
				{
					//Divided in 5 steps
					//<255 239, 239, 239
					//<160 208, 208, 208
					//<125 166, 166, 166
					//<100 139, 140, 139
					//<70 114, 116, 114

					if (ac.r < 255 && ac.r > 160)
					{
						map.setPixel(x, y, sf::Color(239, 239, 239));
					}
					else if (ac.r < 160 && ac.r > 125)
					{
						map.setPixel(x, y, sf::Color(208, 208, 208));
					}
					else if (ac.r < 125 && ac.r > 100)
					{
						map.setPixel(x, y, sf::Color(166, 166, 166));
					}
					else if (ac.r < 100 && ac.r > 75)
					{
						map.setPixel(x, y, sf::Color(139, 140, 139));
					}
					else
					{
						map.setPixel(x, y, sf::Color(217, 192, 117));
					}
				}
				else if (desert == true)
				{
					//Divided in 5 steps
					//<255 248, 208, 85
					//<120 222, 184, 70
					//<100 200, 172, 89
					//<80 188, 165, 94
					//<45 171, 153, 97

					if (ac.r < 255 && ac.r > 122)
					{
						map.setPixel(x, y, sf::Color(248, 208, 85));
					}
					else if (ac.r < 122 && ac.r > 103)
					{
						map.setPixel(x, y, sf::Color(222, 184, 70));
					}
					else if (ac.r < 103 && ac.r > 90)
					{
						map.setPixel(x, y, sf::Color(200, 172, 89));
					}
					else if (ac.r < 90 && ac.r > 75)
					{
						map.setPixel(x, y, sf::Color(188, 165, 94));
					}
					else
					{
						map.setPixel(x, y, sf::Color(217, 192, 117));
					}
				}
				else if (jungle == true)
				{
					//Divided in 6 steps
					//<255 178, 246, 123
					//<115 134, 199, 60
					//<90 131, 181, 73
					//<80 124, 162, 79
					//<75 115, 143, 82
					//<50 98, 116, 78

					if (ac.r < 255 && ac.r > 110)
					{
						map.setPixel(x, y, sf::Color(178, 246, 123));
					}
					else if (ac.r < 110 && ac.r > 104)
					{
						map.setPixel(x, y, sf::Color(134, 199, 60));
					}
					else if (ac.r < 104 && ac.r > 80)
					{
						map.setPixel(x, y, sf::Color(131, 181, 73));
					}
					else if (ac.r < 80 && ac.r > 78)
					{
						map.setPixel(x, y, sf::Color(124, 162, 79));
					}
					else if (ac.r < 78 && ac.r > 75)
					{
						map.setPixel(x, y, sf::Color(115, 143, 82));
					}
					else
					{
						map.setPixel(x, y, sf::Color(217, 192, 117));
					}
				}
				else if (glacier == true)
				{
					map.setPixel(x, y, sf::Color(247, 255, 255));
				}
				else if (frozenOcean == true)
				{
					map.setPixel(x, y, sf::Color(229, 243, 244));
				}
				else if (forest == true)
				{
					//Divided in 5 steps
					//<255 173, 229, 53
					//<125 167, 211, 61
					//<100 163, 191, 67
					//<70 160, 177, 77
					//<50 139, 154, 71

					if (ac.r < 255 && ac.r > 105)
					{
						map.setPixel(x, y, sf::Color(173, 229, 53));
					}
					else if (ac.r < 105 && ac.r > 90)
					{
						map.setPixel(x, y, sf::Color(167, 211, 61));
					}
					else if (ac.r < 90 && ac.r > 80)
					{
						map.setPixel(x, y, sf::Color(163, 191, 67));
					}
					else if (ac.r < 80 && ac.r > 75)
					{
						map.setPixel(x, y, sf::Color(160, 177, 77));
					}
					else
					{
						map.setPixel(x, y, sf::Color(217, 192, 117));
					}
				}
				else if (tundra == true)
				{
					//Divided in 4 steps
					//<255 66, 248, 135
					//<105 62, 220, 118
					//<90 81, 179, 118
					//<80 98, 142, 120

					if (ac.r < 255 && ac.r > 105)
					{
						map.setPixel(x, y, sf::Color(66, 248, 135));
					}
					else if (ac.r < 105 && ac.r > 90)
					{
						map.setPixel(x, y, sf::Color(62, 220, 118));
					}
					else if (ac.r < 90 && ac.r > 80)
					{
						map.setPixel(x, y, sf::Color(81, 179, 118));
					}
					else
					{
						map.setPixel(x, y, sf::Color(217, 192, 117));
					}
				}
				else if (lake)
				{
					//Cannot happen! So nothing
				}
			}

		}
	}

	std::cout << "Generating cloud map..." << std::endl;

	sf::Image cloudImage = sf::Image();
	cloudImage.create(map.getSize().x, map.getSize().y);

	//Generate cloud map from rain map
	for (int x = 0; x < map.getSize().x; x++)
	{
		for (int y = 0; y < map.getSize().y; y++)
		{
			sf::Color rC = rainMap.getPixel(x, y);
			if (rC.r > 210)
			{
				cloudImage.setPixel(x, y, sf::Color(255, 255, 255, rC.r - 80));
			}
			else
			{
				cloudImage.setPixel(x, y, sf::Color(255, 255, 255, 0));
			}
		}
	}

	std::cout << "Done! Getting SFML ready..." << std::endl;

	//---------------------------
	//End of processing
	bool drawCloudKeyPressedLastFrame = false;
	bool drawCloud = false;

	sf::Texture mapTexture = sf::Texture();
	mapTexture.loadFromImage(map);

	sf::Texture cloudTexture = sf::Texture();
	cloudTexture.loadFromImage(cloudImage);

	sf::Sprite mapSprite = sf::Sprite();
	mapSprite.setTexture(mapTexture);
	
	sf::Sprite cloudSprite = sf::Sprite();
	cloudSprite.setTexture(cloudTexture);

	cloudTexture.setSmooth(false);
	mapTexture.setSmooth(false);


	float cloudIntensity = 1;


	sf::Clock dtC = sf::Clock();
	sf::Time dt = sf::Time();
	//The view to be able to move around the map
	sf::View view(sf::FloatRect(0, 0, windowX, windowY));

	dt = dtC.restart();

	mapSprite.setScale(1 / (float)(map.getSize().x / windowX), 1 / (float)(map.getSize().x / windowX));
	cloudSprite.setScale(1 / (float)(map.getSize().x / windowX), 1 / (float)(map.getSize().x / windowX));

	std::cout << "Initializing window..." << std::endl;

	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "DF Map Viewer (Change name...)");

	std::cout << "Starting loop!" << std::endl;

	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "Tatjam's Map Viewer: " << std::endl;
	std::cout << "WASD: Move around" << std::endl;
	std::cout << "Q: Zoom out" << std::endl;
	std::cout << "E: Zoom in" << std::endl;
	std::cout << "SHIFT: Go faster" << std::endl;
	std::cout << "C: Toggle cloud map" << std::endl;
	std::cout << "F5: Export map" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "Exported maps go into /export/" << std::endl;
	std::cout << "Remember to save maps, as they MAY get" << std::endl;
	std::cout << "overwritten when you save another map!" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "Program Log:" << std::endl << std::endl;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::Resized || rescale)
			{
				//First, make the window square:
				if (window.getSize().x != window.getSize().y)
				{
					window.setSize(sf::Vector2u(window.getSize().x, window.getSize().x));
				}
				view.setCenter(0, 0);
				view.setSize(window.getSize().x, window.getSize().y);
				window.setView(view);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			if (drawCloudKeyPressedLastFrame == false)
			{
				drawCloud = !drawCloud;
				drawCloudKeyPressedLastFrame = true;
			}
		}
		/*
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			if (cloudIntensity > 0 && cloudIntensity - (0.1f * dt.asSeconds()) >= 0)
			{
				cloudIntensity -= 0.1f * dt.asSeconds();
			}
			cloudSprite.setColor(sf::Color(255, 255, 255, 255 * cloudIntensity));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			if (cloudIntensity < 1 && cloudIntensity + (0.1f * dt.asSeconds()) <= 1)
			{
				cloudIntensity += 0.1f * dt.asSeconds();
			}

			cloudSprite.setColor(sf::Color(255, 255, 255, 255 * cloudIntensity));
		}
		*/
		else
		{
			drawCloudKeyPressedLastFrame = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			aMoveSpeed = sMoveSpeed;
			aZoomSpeed = sZoomSpeed;
		}
		else
		{
			aMoveSpeed = moveSpeed;
			aZoomSpeed = zoomSpeed;
		}
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			//Zoom out:
			view.setSize(view.getSize().x + -aZoomSpeed * dt.asSeconds(), view.getSize().y + -aZoomSpeed * dt.asSeconds());
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			//Zoom in:
			view.setSize(view.getSize().x - -aZoomSpeed * dt.asSeconds(), view.getSize().y - -aZoomSpeed * dt.asSeconds());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			view.move(0, -aMoveSpeed * dt.asSeconds());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			view.move(-aMoveSpeed * dt.asSeconds(), 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			view.move(0, aMoveSpeed * dt.asSeconds());
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			view.move(aMoveSpeed * dt.asSeconds(), 0);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
		{
			std::stringstream cloudName; 
			cloudName << "export/cloud-" << rand() << ".png";
			std::stringstream mapName;
			mapName << "export/map-" << rand() << ".png";
			std::cout << "Exporting color and cloud map..." << std::endl;
			std::cout << "Exporting map as: " << mapName.str() << std::endl;
			map.saveToFile(mapName.str());
			std::cout << "Exporting clouds as: " << cloudName.str() << std::endl;
			cloudImage.saveToFile(cloudName.str());
			std::cout << "Done!" << std::endl;
		}

		window.clear();
		window.setView(view);
		window.draw(mapSprite);
		if(drawCloud)
			window.draw(cloudSprite);
		window.display();

		dt = dtC.restart();
	}

	return 0;
}
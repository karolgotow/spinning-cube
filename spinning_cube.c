float A, B, C;

		float cubeWidth = 20;
		int width = 80, height = 22;
		float zBuffer[80 * 22];
		char buffer[80 * 22];
		int backgroundASCIICode = ' ';			//zmienne duzo zmiennych
		int distanceFromCam = 100;
		float horizontalOffset;
		float K1 = 40;

		float incrementSpeed = 0.6;

		float x, y, z;
		float ooz;
		int xp, yp;
		int idx;

		float calculateX(int i, int j, int k) //obliczenie polozenie punktu w osi x
			{
			return 
				(
				j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) + 
				j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C)
				);
			}

		float calculateY(int i, int j, int k) //obliczenie polozenie punktu w osi y
			{
				return 
					(
					j * cos(A) * cos(C) + k * sin(A) * cos(C) - 
					j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) - 
					i * cos(B) * sin(C)
					);
			}

		float calculateZ(int i, int j, int k) //obliczenie polozenie punktu w osi z
			{
				return 
					(
					k * cos(A) * cos(B) - 
					j * sin(A) * cos(B) + i * sin(B)
					);
			}

		void calculateForSurface(float cubeX, float cubeY, float cubeZ, int ch) //sprawdzenie ktorej sciany szescianu dotyczy punkt
			{
			x = calculateX(cubeX, cubeY, cubeZ);
			y = calculateY(cubeX, cubeY, cubeZ);
			z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

			ooz = 1 / z;

			xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2);
			yp = (int)(height / 2 + K1 * ooz * y);

			idx = xp + yp * width;
			if (idx >= 0 && idx < width * height) 
				{
				if (ooz > zBuffer[idx]) //harda matma ale ogolem zmienna ooz to wyliczenie czy sciana jest blizej czy dalej ans i jesli jest blizej to wypelnienie nasepuje znakiem sciany ktora jest blizej 
					{
					zBuffer[idx] = ooz;
					buffer[idx] = ch;
					}
				}
			}
void main() {
		int ch;
		int temp;
		while ((temp = getchar()) != '\n' && temp != EOF); //czyscimy bufer inputu
		while (1) 
			{

			fcntl(STDIN_FILENO, F_SETFL, 0 | O_NONBLOCK); //ustawiamy flage inputu zeby nie przerywalo rpacy programu
			ch = getchar();

			if(ch != EOF)
				{
				while ((temp = getchar()) != '\n' && temp != EOF); //obsluga nacisniecia klawisza NETER
				fcntl(STDIN_FILENO, F_SETFL, 0 & ~O_NONBLOCK);
				break;
				}

			memset(buffer, backgroundASCIICode, width * height);	//memsetem czyscimy cala tablice
			memset(zBuffer, 0, width * height * 4);

			// first cube
			cubeWidth = 10;
			horizontalOffset = -2 * cubeWidth; 
			for (float cubeX = -cubeWidth; cubeX < cubeWidth; cubeX += incrementSpeed) 
				{
				for (float cubeY = -cubeWidth; cubeY < cubeWidth;
				   cubeY += incrementSpeed) 
					{
					calculateForSurface(cubeX, cubeY, -cubeWidth, '@');	
					calculateForSurface(cubeWidth, cubeY, cubeX, '$');		//no tutaj sie dzieja obliczenia wierzcholko i wypelnienia miedzy nimi szescianu ergo wstawienie znaku do bufora projekcji
					calculateForSurface(-cubeWidth, cubeY, -cubeX, '~');
					calculateForSurface(-cubeX, cubeY, cubeWidth, '#');
					calculateForSurface(cubeX, -cubeWidth, -cubeY, ';');
					calculateForSurface(cubeX, cubeWidth, cubeY, '+');
					}
				}

			system("clear"); //czyscimy output

			for (int k = 0; k < width * height; k++) //DODAJEME KOLORKI BO TAK JEST LADNIEJ
				{
				//printf("%d",buffer[k]);
				switch (buffer[k])
					{
				    case '@': // Czerwony
					printf("\033[31m"); //w casach mozna dawac chary bo tak naparawde czary to sa inty
					break;
				    case '$': // Zielony
					printf("\033[32m");
					break;
				    case '~': // Żółty
					printf("\033[33m");
					break;
				    case '#': // Niebieski
					printf("\033[34m");
					break;
				    case ';': // Magenta
					printf("\033[35m");
					break;
				    case '+': // Cyan
					printf("\033[36m");
					break;
					}
				putchar(k % width ? buffer[k] : 10); //wczytanie chara z tablicy rpzechowuajcej obraz projekcji szescianu i wpisanie go w output
				}
			printf("\033[0m\nNacisnij ENTER zeby przerwac\n"); 

			A += 0.05;
			B += 0.05; //te zmienne kontroluja predkosc obortu w 3 osciach
			C += 0.01;

			usleep(8000 * 8); //pauza pentli w mikro sekundach czyli to daje nam 8000 us czyli 8 ms razy 8 to jakies 64 mikrosekundy co daje okolo 15 klatek na sekunde, ludzkie oko i tak nie widzi wiecej xD
			}
}


#include <iostream>
#include <string>
#include <unistd.h>//usleep()
#include <SFML/Graphics.hpp>



int main(){

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "Arkanoid");
	window.setFramerateLimit(120);

	//ball
    sf::CircleShape ball(15.f);
    ball.setFillColor(sf::Color(52, 140, 235));
	ball.setPosition(500,600);

	//bricks
	std::vector<std::vector<sf::RectangleShape>> bricks;
	for(int i=0; i<10;i++){
		std::vector<sf::RectangleShape> bricks_row;
		bricks.push_back(bricks_row);
		for(int j=0;j<10;j++){
			sf::RectangleShape brick(sf::Vector2f(60.f, 25.f));
			bricks[i].push_back(brick);
			bricks[i][j].setPosition(60*i*1.2+100,j*25*1.2+25);
		}
	}

	//set bricks texture
	sf::Texture texture;
	if (!texture.loadFromFile("src/brick.jpg"))
	{
		std::cerr << "Failed to load image" << std::endl;
	}
	for(int i=0; i<10;i++){
		std::vector<sf::RectangleShape> bricks_row;
		bricks.push_back(bricks_row);
		for(int j=0;j<10;j++){
			bricks[i][j].setTexture(&texture);
		}
	}



	//bar
	sf::RectangleShape bar(sf::Vector2f(125.f, 5.f));
	bar.setPosition(400,599);

	//set up direction which the ball travels
	int dir_x = 1;
	int dir_y = -1;

	//set up score
	int score = 0;
	sf::Font font;
	if (!font.loadFromFile("src/font_l.ttf")){
    	// error...
	}

	sf::Text text;
	sf::Text score_text;
	sf::Text message;
	// select the font
	text.setFont(font);
	score_text.setFont(font);
	message.setFont(font);
	// set the string to display
	text.setPosition(50,650);
	score_text.setPosition(150,650);
	text.setString("score: ");
	score_text.setString(std::to_string(score));
	// set the character size
	text.setCharacterSize(25);
	score_text.setCharacterSize(25);
	// set the color
	text.setFillColor(sf::Color::White);

	bool gameOver = false;

	//------------------------game start ----------------------------
    while (window.isOpen() && gameOver == false)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		ball.move(dir_x,dir_y);

		//if the ball hit the right edge
		if(ball.getPosition().x>1000){
			dir_x *= -1;
		}

		//if the ball hit the left edge
		if(ball.getPosition().x < 0){
			dir_x *= -1;
		}

		//if the ball hit the top edge
		if(ball.getPosition().y <0){
			dir_y *= -1;
		}

		//if fails to catch ball
		if(ball.getPosition().y >599){
			//print a message
			// set the string to display
			message.setPosition(300,300);
			message.setString("GAME OVER!\n Your score:");
			score_text.setString(std::to_string(score));
			score_text.setPosition(625,350);
			// set the character size
			message.setCharacterSize(50);
			score_text.setCharacterSize(50);
			// set the color
			message.setFillColor(sf::Color::White);
			window.draw(message);
			window.draw(score_text);
	        window.display();
			usleep(3000000);

			gameOver = true;
			break;
		}

		//get ball bounds
		sf::FloatRect ball_bounds = ball.getGlobalBounds();

		//if the ball hit the bar
		sf::FloatRect bar_bounds = bar.getGlobalBounds();
		if(bar_bounds.intersects(ball_bounds)){
			dir_y = -2;
		}

		//if the ball hit the bricks
		for(int i=0; i<10;i++){
			for(int j=0;j<10;j++){
				//get the bounds of the brick
				sf::FloatRect brick_bounds = bricks[i][j].getGlobalBounds();
				if (brick_bounds.intersects(ball_bounds)){ //check if collide
		    		dir_y *= -1;
					bricks[i][j].setPosition(1250,0); //send this brick away
					score++;
					score_text.setString(std::to_string(score));//update score
				}

			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    		// left key is pressed: move our character
    		bar.move(-5.f, 0.f);
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			bar.move(5.f,0.f);
		}

		//check if wins
		if(score == 100){
			//print a message
			message.setPosition(300,300);
			message.setString("You won!\n Your score:");
			score_text.setString(std::to_string(score));
			score_text.setPosition(625,350);
			// set the character size
			message.setCharacterSize(50);
			score_text.setCharacterSize(50);
			// set the color
			message.setFillColor(sf::Color::White);
			window.draw(message);
			window.draw(score_text);
	        window.display();
			usleep(3000000);

			gameOver = true;
			break;
		}

		//clear window
        window.clear();
		//draw bricks
		for(int i=0; i<10;i++){
			for(int j=0;j<10;j++){
				window.draw(bricks[i][j]);
			}
		}
		//draw ball
        window.draw(ball);
		//draw bar
		window.draw(bar);
		window.draw(text);
		window.draw(score_text);
        window.display();
    }

    return 0;
}

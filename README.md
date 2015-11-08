Introduction to Games Programming
Tools and Middleware

Reports:
Introduction to Games Programming
name of the project: _MyInvaderers

I have been working on the invaderers example provided and my intention was developing a game based on the Sprite class. One of the main challenges was to give additional functionality to the space ship. I wanted to give the ability to move faster and in 2D, not just at the bottom of the screen. It took me a while to find the parts of the Octet that govern control over the keyboard. I found it in app_common.h. Using is_key_down() and cumbersome if-else statements to apply translation on the proper direction I managed to achieve it. I used defined constants N,S,E,W,NE,NW,SE,SW to make easier to know where I was assigning the translations to North, South, East, West, North East, North West, South East and South West directions from the current space ship position. Speed was just increased using the variable ship_speed.

My next step was to increase the shooting capacity of the space ship. I needed more keys for such a purpose since the movement of the space ship is controlled by the arrows keys. Therefore, I added more keys in the app_common.h file, starting from key_a = 65; to key_z. Shooting now can be control with the keys �e� for North (up), �s� for West (left), �f� for East (right), and �d� for South (down). Additionally, if you press two keys simultaneously, say �e �and �f�, the missile will be shot on the NorthEast direction, up-right, i.e., along the vector (1,1) from the space ship. It has been quite cumbersome to code all this as it needs a lot of if-else nested statements.

Another functionality I wanted to add was a more dynamic movement of the invaderers (the enemy) on the screen. I wanted to use parametric curves in 2D and I started with (x,y)=(3sin5t,3sin3t). First, I needed to keep record of the time so I used a variable t that is increased in each simulation. Second, I needed to increment time t  in each simulation by a certain value which I used under the name delta. Once all this was set up and the function introduced in the invaderer movement function, I realised that it wasn�t moving correctly. It took me a while but I finally realised that the movement in the invaderers function is described by a translation each frame so therefore the correct equation to have the movement displayed correctly was its differentiated version (dx,dy)=((15cos5t)*delta,(9cos3t)*delta), where delta plays the role of the differential dt.

Next challenge, I set up was to write a fragment shader. And here is where I got stuck most of the time, I manage to give some color to the textures but I needed more technical practice in shading language. I would have added a second texture to play with relieve and make the sprites of the game more �3D�-like. I found it too complicated so, I was going to decide to change the whole structure of the game to have less characters and not based on Sprites but just game objects on scene using add_shapes() where it would be easier for me to write different fragment shaders for each game objet type. There are examples in Octet that are quite clear. But I honestly run out of time.
 I sincerely apologise for my underperformance, I haven�t been able to code my whole idea on the assignment but just a functional version of the invaderers meant just to be a practice to export functionality to my own game.

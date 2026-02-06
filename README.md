<h1>Helm-Of-Offering</h1>

A C++ Project - Using Microcontroller (Arduino Uno R4 Wifi) and electronic components to make an Interactive Physical System.



<h2>Project Description:</h2>

The Helm of offering is a ritualistic machine helmet, that ‘the Marked’ (player 1) puts on once they’ve been chosen by the machine - the Marked is essentially being sacrificed. Once the timer ends, whom ever is left wearing the helmet will be donated to the gods for the sacrificial ceremony. Since there will be 2 types of players... While The Marked is left seeking other life to pass on the helmet. The hiders will try not to be caught. But their job is not going to be that easy. 

 

<h3>How does this meet the theme, Ritual Machines? </h3> 

 

Korebe, a popular Turkish version of blind man’s buff. Which has one person blindfolded and the rest avoiding getting caught by the blindfolded. Now and then other players must call out to the blindfolded to hint their whereabouts.  

 

<h3>Ritual Element:</h3> 

- Repeated actions for instance, blind folded person tries to catch others. And vice versa other players try to get away from the blind folded.  

- Round Begins when ‘the Marked’ is selected 

- Calling out to the blind folded. We’ve altered this where there will be an auditory cue for the marked to hear whenever the other player stands still for an extended period.  

 

<h3>Machine Element:</h3> 

- The Helm of Offering (the helmet) is the machine that enforces the ritual. It does this by selecting a player to become the marked at the beginning. 

- The electronic components attach to the helmet to help the blinded to find others. 

- Lastly, the helmet will at the end initiate the sacrifice.


<h2>Project Operation:</h2>

<h3>Instructions to players participating in the sacrificial ceremony:</h3>

 

- Each Player will have to place their hand on the conductive part of the helmet; the helm of offering will choose the first marked. If the helmet’s eyes glow red for an extended period, then that person is marked.  

- The marked will place the helmet over their head and wait for the hunt to commence. 

- The second player will have a staff. The staff is a part of the helm of offering; it can sense if the player isn’t moving for a period (3.5 seconds). If the player is sensed to not be moving for this period, then there will be a loud buzzing sound, which the     marked will be able to hear.  

- Once the hunt commences; both players have 5 minutes. In this period, the goal of the marked is to pass on the helmet to the other player. Once the hunt ends, the player with the helmet is the sacrifice.  

- The Helmet is equipped with an ultrasonic sensor; players within the vicinity of the ultrasounds will be picked up by the helmet. If the marked manages to touch the other player, they swap roles. 

- The staff is equipped with a flashlight; this flashlight can disable the ultrasonic sensor for 3 seconds. This window of opportunity allows the second player to escape the reach of the marked.


<h2>Contribution:</h2>

- In this Group Project, We divided programming equally between us. I was tasked with producing an algorithm for the staff using a MPU6050 Gyroscope, and also player selection algorithm for the helmet.

<h3>Helmet Code:</h3> 

- Below is a code snippet of the player selection Algoirthm. Which was produced by making a basic circuit with a capacitor and resistors, then using one side to supply 5V and then an analog pin to read data. We we're able to construct a simple algorithm that when a person places hands on the conductive piece of the circuit, they'll essenially be acting as a 'Switch' that'll be connecting the circuit together, in which we're able to received data and measure differences as human are a natural resistors. Therefore, we were able to determine whenever there was a connection or not. 

<img width="450" height="1207" alt="Screenshot 2026-02-06 163755" src="https://github.com/user-attachments/assets/546ea7e3-528b-4ac4-b2e6-f3dca04b42ea" />

<h3>Staff Code:</h3> 

- Using the MPU6050 Libary for the gyroscope, I was able to calculate whether the player was moving or not by using the raw data received by the gyroscope. 
<img width="453" height="899" alt="Screenshot 2026-02-06 163610" src="https://github.com/user-attachments/assets/fba9bbe7-9937-4db3-9d58-cf04ab677b47" />
<img width="686" height="825" alt="Screenshot 2026-02-06 163622" src="https://github.com/user-attachments/assets/c1f7286b-cd02-4cd4-9504-8a5974dd9516" />

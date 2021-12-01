# Deaf-Blind-Communication-Interface
Bi-directional Communication Inteface based on uniquely Decipherable  Morse Code

many attempts have been  made to  provide a communication interface for DeafBlind  person  but all of them are suffering from 2 critical flaws  which is  impending their mass use.
1) parsing morse code is  time dependent wait just a bit long and your input is  parsed into  some  other symbol
 ex h = 0000  but  it  can get  parsed as eeee, ii and many  more 
 see  this  https://drive.google.com/file/d/1bC2JHh23IV9pXJjxF8p6_V7r-J1JqnDC/view?usp=sharing where I discuss this  problem.

Morse code has a design  flaw, it is variable  length code with non unique codewords that was developed before the age of Information theory
lets  say look for codeword h = 0000
                            e=0
                            i=00
                            s=000 
how do we  determine in a variable length code which is not unique what code 00 represents is it i or ee ?
I solved this  problem by hardware  design, thanks to lecture from Prof Dan Gusfield. I will reveal it in  a paper. on this topic
My Demo of fixed morse code as input.
https://drive.google.com/file/d/1bX9ewWTQ0mOQovoBOaG8twWIj51ZRmau/view?usp=sharing
 
2) unavailability  of physical button that give  a tactile  feedback
 for some one  who is  deaf and  blind its hard to see  which area is  for  input and if his  input is interpreted  correctly as there is no  feedback to  the  person. 
 But with 3 physical buttons embossed with symbols like in braille we can solve this  problem. This works in case of laptops and desktop
 But how to add  physical buttons to phones that have touchscreens. I managed to hack the 3.5 mm jack and interface a circuit and was able to add 3 tactile momentary switches.
 https://drive.google.com/file/d/1bKgJGCpCFcjjOEfLsvuRZwH7EukwpoRQ/view?usp=sharing
 

#include "SDLHelper.h"

#include "SDL/SDL.h"

#include "Tamagotchi.h"

 

 

Tamagotchi::Tamagotchi()

{

 

}

 
011
void Tamagotchi::setName(string name)
012
{
013
    this->name = name;
014
}
015
 
016
string Tamagotchi::getName()
017
{
018
    return name;
019
}
020
 
021
int Tamagotchi::getHunger()
022
{
023
    return hunger;
024
}
025
 
026
void Tamagotchi::setHunger(int hunger)
027
{
028
    this->hunger = hunger;
029
}
030
 
031
int Tamagotchi::getState()
032
{
033
    return state;
034
}
035
 
036
void Tamagotchi::setState(int state)
037
{
038
    this->state = state;
039
}
040
 
041
SDLSurface *Tamagotchi::getScreen()
042
{
043
    return screen;
044
}
045
 
046
/*
047
 * Check e.g. button clicked on
048
 */
049
int isRectContains(SDL_Rect*rect, int x, int y)
050
{
051
    if(((x >= rect->x) && (x <= (rect->x+rect->w))) &&
052
            ((y >= rect->y) && (y <= rect->y+rect->h)))
053
        return 1;
054
    else
055
        return 0;
056
}
057
 
058
 
059
/*
060
 * Process mouse clicks
061
 */
062
int Tamagotchi::doMouseclick(int x, int y)
063
    {
064
 
065
    /*
066
     * lab 5 - put code in FeedButton class
067
     *
068
     */
069
    if(isRectContains(&this->feedButton->rect,x,y)) {
070
        /*
071
         * Move code to FeedButton process click instead of here
072
         */
073
 
074
        if(getHunger() > 10) {
075
            /*
076
             * "Animated" eating...
077
             *
078
             */
079
            setState(EATING);
080
            for(int i=0;i<10;i++) {
081
                setHunger(getHunger()-1);
082
                hungerBar->rect.w = hunger;
083
                hungerBar->draw(screen);
084
                drawFeedingFace(); // one approach - set different Body states & then redraw face
085
                screen->Flip();
086
                screen->Delay(50);
087
                drawFace();
088
                screen->Flip();
089
            }
090
            setState(NORMAL);
091
        }
092
 
093
        return 0;
094
    }
095
 
096
    if(isRectContains(&this->playButton->rect,x,y)) {
097
        /*
098
         * Move code to PlayButton process click instead of here
099
         */
100
 
101
        if(getHunger() < 300) {
102
            /*
103
             * "Animated" playing...
104
             *
105
             */
106
 
107
            for(int i=0;i<10;i++) {
108
                setHunger(getHunger()+1);
109
                hungerBar->rect.w = hunger;
110
                hungerBar->draw(screen);
111
                setState(PLAYING); // alternative approach - change Tamagotchi's state & redraw face
112
                drawFace();
113
                screen->Flip();
114
                screen->Delay(50);
115
                setState(NORMAL);
116
                drawFace();
117
                screen->Flip();
118
            }
119
 
120
        }
121
 
122
        return 0;
123
    }
124
 
125
      cout << "Mouse at: " << x << ", " << y << endl;
126
 
127
      return 0;
128
    }
129
 
130
 
131
// Wait for the user to click
132
int Tamagotchi::waitForMouse()
133
  {
134
  SDL_Event event;
135
  string text = "";
136
  /* Loop waiting for ESC+Mouse_Button */
137
 
138
  while ( SDL_WaitEvent(&event) >= 0 )
139
    {
140
    switch (event.type)
141
      {
142
    case SDL_KEYDOWN :
143
    {
144
        cout << "key down: ";
145
        break;
146
    }
147
      case SDL_MOUSEBUTTONDOWN:
148
        {
149
        cout << "Mouse button pressed" << endl;
150
        this->doMouseclick(event.motion.x, event.motion.y);
151
        // return 1;
152
        break;
153
        }
154
      case SDL_QUIT:
155
        {
156
        cout << "Quit requested, quitting." << endl;
157
        return(0);
158
        }
159
      }
160
    }
161
  }
162
 
163
 
164
void Tamagotchi::setUpFace()
165
{
166
    body = new Body();
167
 
168
    body->head = new Head("head",50,50,700,500);
169
    body->addElement(body->head);
170
 
171
    body->left_eye = new Eye("lefteye",250,250,30,30);
172
    body->right_eye = new Eye("righteye",450,250,30,30);
173
    body->addElement(body->left_eye);
174
    body->addElement(body->right_eye);
175
 
176
    body->mouth = new Mouth("mouth",350,400,70,30);
177
    body->addElement(body->mouth);
178
}
179
 
180
/*
181
 *
182
 * lab 5 - Move the drawing code to Body & Control subclasses
183
 * as appropriate...
184
 *
185
 */
186
 
187
/**
188
 * Draw "eye"
189
 */
190
void Tamagotchi::drawEye(Eye *e)
191
{
192
    /* Using SDLSurface helper functions */
193
      int colour = screen->getColour(0,0,100);
194
      if(getState() == PLAYING) // could also set Eye state to "playing"
195
          colour = screen->getColour(50,50,0);
196
 
197
      screen->FillRect(e->x,e->y,e->w,e->h,colour);
198
}
199
 
200
/**
201
 * Draw "mouth"
202
 */
203
void Tamagotchi::drawMouth(Mouth *m)
204
{
205
    /*
206
     * Using SDL C functions direct - yucky!
207
     */
208
      SDL_Rect rect1;
209
      rect1.x=m->x;rect1.y=m->y;rect1.w=m->w;rect1.h=m->h;
210
      int colour = screen->getColour(0,0,100);
211
      if(m->feeding)
212
          colour = screen->getColour(50,50,0);
213
      SDL_FillRect(screen->screen,&rect1,colour);
214
}
215
 
216
/**
217
 * Draw "head"
218
 */
219
void Tamagotchi::drawHead(Head *e)
220
{
221
    /* Using "nice" SDLSurface helper function */
222
      screen->FillRect(e->x,e->y,e->w,e->h,0,0,100);
223
      screen->FillRect(e->x+20,e->y+20,e->w-40,e->h-40,100,100,100);
224
}
225
 
226
/**
227
 * Draw "name" label
228
 */
229
void Tamagotchi::drawName()
230
{
231
    screen->DrawText(screen->font36, 20, 5, "Freddo");
232
}
233
 
234
 
235
 
236
 
237
void Tamagotchi::drawFace()
238
{
239
      // Exercise #5, part 2 - refactor so code to draw relocated to
240
      // the various BodyElement subclasses vs here in the Tamagotchi class...
241
      //
242
      // You could do e.g. body->head->drawElement() etc
243
      //   or nicer still, body->drawBody() ...
244
 
245
    drawHead(body->head);
246
    drawEye(body->left_eye);
247
    drawEye(body->right_eye);
248
    drawMouth(body->mouth);
249
}
250
 
251
void Tamagotchi::drawFeedingFace()
252
{
253
      // Exercise #5, part 2 - refactor so code to draw relocated to
254
      // the various BodyElement subclasses vs here in the Tamagotchi class...
255
      //
256
 
257
    drawHead(body->head);
258
    drawEye(body->left_eye);
259
    drawEye(body->right_eye);
260
    body->mouth->feeding = true;
261
    drawMouth(body->mouth);
262
    body->mouth->feeding = false;
263
}
264
 
265
void Tamagotchi::drawPlayingFace()
266
{
267
      // Exercise #5, part 2 - refactor so code to draw relocated to
268
      // the various BodyElement subclasses vs here in the Tamagotchi class...
269
      //
270
 
271
    drawHead(body->head);
272
    body->left_eye->playing = true;
273
    body->right_eye->playing = true;
274
    drawEye(body->left_eye);
275
    drawEye(body->right_eye);
276
    body->left_eye->playing = false;
277
    body->right_eye->playing = false;
278
    drawMouth(body->mouth);
279
 
280
}
281
 
282
void Tamagotchi::drawScreen()
283
{
284
 
285
      // screen background
286
      screen->FillRect(50,50,700,500,100,100,100);
287
 
288
 
289
      // draw the labels
290
      //
291
      //
292
      drawName();
293
 
294
      drawFace();
295
 
296
      // draw the controls
297
      feedButton->draw(screen);
298
      playButton->draw(screen);
299
      hungerBar->draw(screen);
300
 
301
      //Flip the backbuffer to the primary
302
      screen->Flip();
303
}
304
 
305
 
306
void Tamagotchi::initialise()
307
{
308
    name = "Freddo";
309
    hunger = 200;
310
    tiredness = 0;
311
    boredness = 100;
312
     state = NORMAL;
313
 
314
     feedButton = new FeedButton("Feed",280,540,100,60);
315
     playButton = new PlayButton("Play",400,540,100,60);
316
     hungerBar = new HungerBar("Hunger",280,20,20,20);
317
 
318
     hungerBar->rect.w = hunger;
319
 
320
     setState(NORMAL);
321
 
322
     setUpFace();
323
 
324
     screen = SDLSurfaceFactory::getInstance()->newSurface(800,600);
325
}
326
 
327
/*
328
 * Observer operations
329
 */


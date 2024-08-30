# simple exponential animation curve for ui

source: [Ryan Fleury](https://www.rfleury.com/)

> I have often raved about a very simple animation algorithm that requires very little extra state tracking and is very useful in UI animation, for low-cost juicing: 
> 
> ```txt
> value += (target - value) * rate
> ```
> 
> While explaining this to someone in the comments of my last article on UI, I set up a Desmos with the closed-form version of the curve that results from this. In it, you can see the strategy for calculating a rate `r` based on `f` (refresh rate Hz) that will ensure that the number of seconds it takes to complete the animation (`z` / `f`) is constant, for that rate and a given target: https://www.desmos.com/calculator/xwerlmi4cs

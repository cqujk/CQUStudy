package org.controller;

public abstract class Controller {
    public abstract void run();
    public abstract void stop();
    public abstract void pause();
    public abstract void resume();
    public abstract void reset();
    public void show(){};

}

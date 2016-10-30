/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <clement@decoodt.eu> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Clement Decoodt
 * ----------------------------------------------------------------------------
 */

#pragma once

void printUsage();

void init();

void reshape(int w, int h);

void display();

void keyboard (unsigned char keyPressed, int x, int y);

void mouse (int button, int state, int x, int y);

void motion (int x, int y);

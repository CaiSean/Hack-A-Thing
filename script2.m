% Housekeeping
clc; 
clear all; 

%% Import the image
img = imread('Sample_1.jpg'); 
img = imresize(img,0.5); 

%% Low-level image processing
img_gray = rgb2gray(img); 
% img_histeq = histeq(img_gray); 
% imhist(img_histeq)
img_BW = imbinarize(img_gray); 
img_BW = imcomplement(img_BW); 
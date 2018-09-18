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

%% Boundary detection
img_edge = edge(img_BW);
B = bwboundaries(img_edge, 'holes');
figure; 
imshow(img_edge)

for i = 1:length(B)
    cell_length(i, :) = length(B{i}); 
    cell_length_sort = sort(cell_length, 'descend'); 
end


for i = 1:length(B)
    for j = 1:7
        if length(B{i}) == cell_length_sort(j)
            important_feature{j, :} = B{i}; 
        end
    end
end

%% Plot the boundaries
figure; 
imshow(img_edge)
hold on

for k = 1:length(important_feature)
    cell_plot = important_feature{k}; 
    scatter(cell_plot(:, 2), cell_plot(:, 1), 3,'r','*')
end
hold off

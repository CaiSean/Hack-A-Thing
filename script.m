% Housekeeping
clc; 
clear all; 

% Import the image
img = imread('Sample_2.jpg'); 
img = imresize(img,0.5); 

% Low-level image processing
img_gray = rgb2gray(img); 
% img_histeq = histeq(img_gray); 
% imhist(img_histeq)
img_BW = imbinarize(img_gray); 
img_BW = imcomplement(img_BW); 

% Boundary detection
% img_edge = edge(img_BW);
img_edge = bwmorph(img_BW,'bothat');

[H,theta,rho] = hough(img_edge);
P = houghpeaks(H,15,'threshold',ceil(0.5*max(H(:))));
lines = houghlines(img_edge,theta,rho,P,'FillGap',2,'MinLength',10);

figure, imshow(img), hold on
max_len = 0;
for k = 1:length(lines)
   xy = [lines(k).point1; lines(k).point2];
   plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');

   % Plot beginnings and ends of lines
   plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','yellow');
   plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red');

   % Determine the endpoints of the longest line segment
   len = norm(lines(k).point1 - lines(k).point2);
   if ( len > max_len)
      max_len = len;
      xy_long = xy;
   end
end
% highlight the longest line segment

%%
B = bwboundaries(img_edge, 'holes');


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

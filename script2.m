% Housekeeping
clc; 
clear all; 

%% Import the image
img = imread('Sample_1.jpg'); 
img = imresize(img,0.5); 

%% Low-level image processing
img_gray = rgb2gray(img); 
img_BW = imbinarize(img_gray); 
img_BW = imcomplement(img_BW); 

BW2_1 = bwmorph(img_BW,'remove');
% BW2 = imcomplement(BW2);
figure; 
imshow(BW2_1)
% BW2_1 = bwmorph(BW2,'tophat', 10);
% BW2 = BW2 - imcomplement(BW2_1); 
% BW2 = bwmorph(BW2,'thicken');

BW2_2 = bwmorph(img_BW,'branchpoints');
% BW2 = imcomplement(BW2);
figure; 
imshow(BW2_2)

BW2 = BW2_2+ imcomplement(BW2_1); 
figure; 
imshow(BW2)

BW2 = bwmorph(BW2,'thicken', 4);
BW2 = bwmorph(BW2,'bothat');
% BW2 = imcomplement(BW2);
figure; 
imshow(BW2)

% [H,theta,rho] = hough(BW2);
% P = houghpeaks(H,10,'threshold',ceil(0.5*max(H(:))));
% lines = houghlines(BW2,theta,rho,P,'FillGap',5,'MinLength',7);
% 
% figure, imshow(img), hold on
% max_len = 0;
% for k = 1:length(lines)
%    xy = [lines(k).point1; lines(k).point2];
%    plot(xy(:,1),xy(:,2),'LineWidth',2,'Color','green');
% 
%    % Plot beginnings and ends of lines
%    plot(xy(1,1),xy(1,2),'x','LineWidth',2,'Color','yellow');
%    plot(xy(2,1),xy(2,2),'x','LineWidth',2,'Color','red');
% 
%    % Determine the endpoints of the longest line segment
%    len = norm(lines(k).point1 - lines(k).point2);
%    if ( len > max_len)
%       max_len = len;
%       xy_long = xy;
%    end
% end

%% 
B = bwboundaries(BW2, 'noholes');


for i = 1:length(B)
    cell_length(i, :) = length(B{i}); 
    cell_length_sort = sort(cell_length, 'descend'); 
end


for i = 1:length(B)
    for j = 2:11
        if length(B{i}) == cell_length_sort(j)
            important_feature{j, :} = B{i}; 
        end
    end
end

% Plot the boundaries
figure; 
imshow(BW2)
hold on

for k = 1:length(important_feature)
    cell_plot = important_feature{k}; 
    scatter(cell_plot(:, 2), cell_plot(:, 1),3, 'r','*')
end
hold off

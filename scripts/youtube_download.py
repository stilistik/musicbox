import os
import youtube_dl

# Set the location to save the downloaded videos
save_location = '/Users/philippgerber/Desktop/musicbox/music'

# Set the URLs to download
urls = [
    'https://www.youtube.com/watch?v=45B7H7uGDGk',
    'https://www.youtube.com/watch?v=WU1Uwc6OHVk',
    'https://www.youtube.com/watch?v=VNEyRhlrjiA',
    'https://www.youtube.com/watch?v=xRS4vnLWssg',
]

# Set the options for youtube-dl
ydl_opts = {
    'format':
    'bestaudio/best',
    'outtmpl':
    os.path.join(save_location, '%(title)s.%(ext)s'),
    'postprocessors': [{
        'key': 'FFmpegExtractAudio',
        'preferredcodec': 'wav',
        'preferredquality': '192',
    }],
}

# Download the videos
with youtube_dl.YoutubeDL(ydl_opts) as ydl:
    for url in urls:
        ydl.download([url])

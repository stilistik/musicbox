import os
import youtube_dl

# Set the location to save the downloaded videos
save_location = '/Users/philippgerber/Desktop/musicbox/downloads'

# Set the URLs to download
urls = [
    'https://www.youtube.com/watch?v=L70jsue-wEg',
    'https://www.youtube.com/watch?v=oIKt5p3UmXg',
    'https://www.youtube.com/watch?v=jIyVB1b2aBs',
    'https://www.youtube.com/watch?v=Ll7l2KXygNg',
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
        'ar': '44100',
    }],
}

# Download the videos
with youtube_dl.YoutubeDL(ydl_opts) as ydl:
    for url in urls:
        ydl.download([url])

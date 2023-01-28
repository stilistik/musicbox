import os
import youtube_dl

# Set the location to save the downloaded videos
save_location = '/Users/philippgerber/Desktop/musicbox/downloads'

# Set the URLs to download
urls = [
    'https://www.youtube.com/watch?v=VSuDGPBzHAA',
    'https://www.youtube.com/watch?v=nszQak1noAk',
    'https://www.youtube.com/watch?v=j9963chszKA',
    'https://www.youtube.com/watch?v=ysI-r9yqNmk',
    'https://www.youtube.com/watch?v=BbG7NoVPxjY',
    'https://www.youtube.com/watch?v=60GiSucMaYA',
    'https://www.youtube.com/watch?v=0ILvyLIRTnI',
    'https://www.youtube.com/watch?v=Y6ZGd2fbSLk',
    'https://www.youtube.com/watch?v=sGiT-qAM1GA',
    'https://www.youtube.com/watch?v=PirhZnM8S7M',
    'https://www.youtube.com/watch?v=M6LzToyUnaE',
    'https://www.youtube.com/watch?v=TlgeHJw8elY',
    'https://www.youtube.com/watch?v=aFkCo2WWE7M',
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
    'postprocessor_args': ['-ar', '44100'],
}

# Download the videos
with youtube_dl.YoutubeDL(ydl_opts) as ydl:
    for url in urls:
        ydl.download([url])

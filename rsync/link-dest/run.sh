# This was to emulate scenario where mint had Docs & Music,
# initially thyme had only Docs, but later got (some) Music,
# and I wanted to link thyme's backup to both its previous backup for Docs,
# and to mint's backup for Music.

set echo

rsync -av mint/Docs thyme

rsync -av mint/ mint-backup-1

# Note link-dest works best with abs. paths: ${cwd}/mint-backup-1
# With relative paths, it is relative to the destination.
rsync -av --link-dest ${cwd}/mint-backup-1 mint/ mint-backup-2

rsync -av thyme/ thyme-backup-1

rsync -av --link-dest ${cwd}/thyme-backup-1 thyme/ thyme-backup-2

rsync -av mint/Music thyme

rsync -av --link-dest ${cwd}/thyme-backup-1 \
          --link-dest ${cwd}/mint-backup-2 thyme/ thyme-backup-2

ls -li */Music/U2/c.mp3
ls -li */Docs/foo/bar.txt

unset echo

# Note all 3 backups have same 4437857 inode.
# ls -li */Music/U2/c.mp3
# 4437857  ...  mint-backup-1/Music/U2/c.mp3
# 4437857  ...  mint-backup-2/Music/U2/c.mp3
# 4384944  ...  mint/Music/U2/c.mp3
# 4437857  ...  thyme-backup-2/Music/U2/c.mp3
# 4437891  ...  thyme/Music/U2/c.mp3

# Note both mint backups have same 4437853 inode,
# and both thyme backups have same 4437877 inode.
# ls -li */Docs/foo/bar.txt
# 4437853  ...  mint-backup-1/Docs/foo/bar.txt
# 4437853  ...  mint-backup-2/Docs/foo/bar.txt
# 4384952  ...  mint/Docs/foo/bar.txt
# 4437877  ...  thyme-backup-1/Docs/foo/bar.txt
# 4437877  ...  thyme-backup-2/Docs/foo/bar.txt
# 4437845  ...  thyme/Docs/foo/bar.txt

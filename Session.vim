let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Development/of_v0.10.0_linux64gcc6_release/apps/myApps/rosendal
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 src/ofApp.h
badd +47 src/ofApp.cpp
badd +1 ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.h
badd +217 ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.cpp
badd +24 ../../../addons/ofxBullet/src/shapes/ofxBulletCustomShape.h
badd +1 src/Player.h
badd +106 src/Player.cpp
argglobal
silent! argdel *
$argadd src/ofApp.h
set stal=2
tabnew
tabnext -1
edit src/ofApp.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 72 + 74) / 148)
exe 'vert 2resize ' . ((&columns * 75 + 74) / 148)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 46 - ((45 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
46
normal! 0
wincmd w
argglobal
if bufexists('src/ofApp.h') | buffer src/ofApp.h | else | edit src/ofApp.h | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 34 - ((33 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
34
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 72 + 74) / 148)
exe 'vert 2resize ' . ((&columns * 75 + 74) / 148)
tabnext
edit src/Player.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 73 + 74) / 148)
exe 'vert 2resize ' . ((&columns * 74 + 74) / 148)
argglobal
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 106 - ((103 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
106
normal! 049|
wincmd w
argglobal
if bufexists('src/Player.h') | buffer src/Player.h | else | edit src/Player.h | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 14 - ((13 * winheight(0) + 52) / 105)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
14
normal! 057|
wincmd w
exe 'vert 1resize ' . ((&columns * 73 + 74) / 148)
exe 'vert 2resize ' . ((&columns * 74 + 74) / 148)
tabnext 1
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
set winminheight=1 winminwidth=1
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :

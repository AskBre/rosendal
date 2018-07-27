let SessionLoad = 1
if &cp | set nocp | endif
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
cd ~/Development/of_v0.10.0_linux64gcc6_release/apps/myApps/rosendalModel
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 src/ofApp.h
badd +37 src/ofApp.cpp
badd +1 ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.h
badd +89 ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.cpp
badd +0 ../../../addons/ofxBullet/src/shapes/ofxBulletCustomShape.h
argglobal
silent! argdel *
$argadd src/ofApp.h
set stal=2
edit src/ofApp.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=1 winheight=1 winminwidth=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 131 + 134) / 269)
exe 'vert 2resize ' . ((&columns * 137 + 134) / 269)
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
let s:l = 46 - ((45 * winheight(0) + 48) / 96)
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
let s:l = 34 - ((32 * winheight(0) + 48) / 96)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
34
normal! 017|
wincmd w
exe 'vert 1resize ' . ((&columns * 131 + 134) / 269)
exe 'vert 2resize ' . ((&columns * 137 + 134) / 269)
tabedit ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=1 winheight=1 winminwidth=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 134 + 134) / 269)
exe 'vert 2resize ' . ((&columns * 134 + 134) / 269)
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
let s:l = 89 - ((47 * winheight(0) + 48) / 96)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
89
normal! 0
wincmd w
argglobal
if bufexists('../../../addons/ofxBullet/src/shapes/ofxBulletCustomShape.h') | buffer ../../../addons/ofxBullet/src/shapes/ofxBulletCustomShape.h | else | edit ../../../addons/ofxBullet/src/shapes/ofxBulletCustomShape.h | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 24 - ((23 * winheight(0) + 48) / 96)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
24
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 134 + 134) / 269)
exe 'vert 2resize ' . ((&columns * 134 + 134) / 269)
tabedit ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.cpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
set nosplitright
wincmd t
set winminheight=1 winheight=1 winminwidth=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 134 + 134) / 269)
exe 'vert 2resize ' . ((&columns * 134 + 134) / 269)
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
let s:l = 217 - ((48 * winheight(0) + 48) / 96)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
217
normal! 071|
wincmd w
argglobal
if bufexists('../../../addons/ofxBullet/CustomShapesExample/src/ofApp.h') | buffer ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.h | else | edit ../../../addons/ofxBullet/CustomShapesExample/src/ofApp.h | endif
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 48) / 96)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 134 + 134) / 269)
exe 'vert 2resize ' . ((&columns * 134 + 134) / 269)
tabnext 2
set stal=1
if exists('s:wipebuf') && s:wipebuf != bufnr('%')
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

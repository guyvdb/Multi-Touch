
ROOT = File.dirname(__FILE__)

task :clean do

  # files
  files = [
    "**/Makefile",
    "linux/libmt.*",
    "linux/pc",
    "linux/dm",
    "linux/table",
    "linux/tiled",
    "linux/tmxviewer",
    "linux/tuio",
    "linux/pipeline",
    "linux/*.so*",
    "build/*",
    "contrib/qjson/build/*",
    "contrib/tiled/bin/*",
    "contrib/qjson/CMakeLists.txt.user",
    "**/*.o",    
    "**/moc_*",    
    "**/ui_*",
    "**/*~"
  ]

  files.each do |p|
    pattern = File.join(ROOT,p)
    Dir.glob(pattern).each do |file|
      system("rm -rf #{file}")
    end
  end

  #directories
  dirs = [
    "contrib/tiled/build",
    "contrib/qjson/build"
  ]

  dirs.each do |d|
    name = File.join(ROOT,d)
    system("rm -rf #{name}") if File.directory?(name)
  end
  

end

#pragma once
#include "../db/Database.hpp"
#include &lt;type_traits&gt;
#include &lt;vector&gt;

template&lt;typename T&gt;
concept SociCompatible = requires(T a, soci::values&amp; v) {
    { a.into(v) } -> std::same_as&lt;void&gt;;
    { T::tableName() } -> std::convertible_to&lt;std::string&gt;;
};

template&lt;typename T&gt; 
requires SociCompatible&lt;T&gt;
class BaseRepository {
protected:
    soci::session&amp; sql_;
    
public:
    BaseRepository() : sql_(Database::getInstance().getSession()) {}
    
    virtual void create(const T&amp; entity) {
        soci::statement st = (sql_.prepare
            &lt;&lt; "INSERT INTO " + T::tableName() + " VALUES(:values)", 
            soci::use(entity));
        st.execute(true);
    }
    
    virtual T read(int id) {
        T entity;
        sql_ &lt;&lt; "SELECT * FROM " + T::tableName() + " WHERE id = :id",
               soci::into(entity),
               soci::use(id);
        return entity;
    }
    
    virtual std::vector&lt;T&gt; findAll() {
        std::vector&lt;T&gt; results;
        sql_ &lt;&lt; "SELECT * FROM " + T::tableName(), soci::into(results);
        return results;
    }
    
    virtual void update(const T&amp; entity) {
        sql_ &lt;&lt; "UPDATE " + T::tableName() + " SET nome = :nome WHERE id = :id",
               soci::use(entity);
    }
    
    virtual void remove(int id) {
        sql_ &lt;&lt; "DELETE FROM " + T::tableName() + " WHERE id = :id",
               soci::use(id);
    }
};


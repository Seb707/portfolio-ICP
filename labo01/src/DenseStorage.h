#pragma once

/**
 * @file DenseStorage.h
 *
 * @brief Stockage dense pour des données à taille fixe ou dynamique.
 *
 * Nom:
 * Code permanent :
 * Email :
 *
 */

#include <cstring>
#include <cassert>

namespace gti320
{
    enum SizeType { Dynamic = -1 };

    /**
     * Stockage à taille fixe.
     *
     * Le nombre de données à stocker est connu au moment de la compilation.
     * Ce nombre est donné par le paramètre de patron : _Size
     *
     * Un tampon (tableau) de taille `_Size` est alloué sur la pile d'exécution.
     */
    template <typename _Scalar, int _Size>
    class DenseStorage
    {
    private:
        /** 
         * Déclarer une variable m_data sur la pile et allouer la mémoire
         * pour y stocker _Size éléments
         */
        _Scalar m_data[_Size];

    public:
        /** Constructeur par défaut */
        DenseStorage() {}

        /** Constructeur de copie */
        DenseStorage(const DenseStorage& other) { 
            memcpy(m_data, other.m_data, sizeof(_Scalar)* _Size);
        }

        /**
         * Constructeur avec taille spécifiée.
         * Doit être la même que la taille spécifiée dans le patron.
         */
        explicit DenseStorage(int _size) { assert(_size > 0 && _size == _Size); }

        /** Constructeur avec taille (_size) et données initiales (_data). */
        explicit DenseStorage(const _Scalar* _data, int _size)
        {
            assert(_size > 0 && _size == _Size);
            memcpy(m_data, _data, sizeof(_Scalar) * _size);
        }

        /** Opérateur de copie */
        DenseStorage& operator=(const DenseStorage& other)
        {
            if (this != &other)
            {
                assert(other.size() == _Size);
                memcpy(m_data, other.m_data, sizeof(_Scalar)*_Size);
            }
            return *this;
        }

        /** Retourne la taille du tampon */
        static int size() { return _Size; }

        /** Redimensionne le stockage pour qu'il contienne `size` élément. */
        void resize(int size)
        {
            // Invalide pour les matrices à taille fixe.
            assert(false);
        }

        /** Mets tous les éléments à zéro */
        void setZero()
        {
            memset(m_data, 0, sizeof(_Scalar) * _Size);
        }

        /** Accès au tampon de données (en lecteur seulement) */
        const _Scalar* data() const { return m_data; }

        /** Accès au tampon de données (pour lecture et écriture) */
        _Scalar* data() { return m_data; }
    };

    /**
     * Stockage à taille dynamique.
     *
     * Le nombre de données à stocker est déterminé à l'exécution.
     * Un tampon de la taille demandée doit être alloué sur le tas via
     * l'opérateur `new []` et la mémoire doit être libérée avec `delete[]`
     */
    template <typename _Scalar>
    class DenseStorage<_Scalar, Dynamic>
    {
    private:
        _Scalar* m_data;
        int m_size;

    public:
        /** Constructeur par défaut */
        DenseStorage() : m_data(nullptr), m_size(0) {}

        /** Constructeur avec taille spécifiée */
        explicit DenseStorage(int _size) : m_data(nullptr), m_size(_size)
        {
            m_data = new _Scalar[m_size]{ 0 };
        }

        /** Constructeur de copie */
        DenseStorage(const DenseStorage& other) : m_data(nullptr), m_size(other.m_size)
        {
            m_data = new _Scalar[m_size];
            memcpy(m_data, other.m_data, sizeof(_Scalar)*m_size);
        }

        /** Opérateur de copie */
        DenseStorage& operator=(const DenseStorage& other)
        {
            if (this != &other)
            {
                //(*this).resize(other.m_size);
                //assert((*this).m_size == other.m_size);
                memcpy(m_data, other.m_data, sizeof(_Scalar)*other.m_size);
            }
            return *this;
        }

        /** Destructeur */
        ~DenseStorage()
        {
            delete []m_data;
        }

        /** Retourne la taille du tampon */
        inline int size() const { return m_size; }

        /**
         * Redimensionne le tampon alloué pour le stockage.
         * La mémoire qui n'est plus utilisée doit être libérée.
         *
         * Note :​ Les opérations de redimensionnement entraînent une réallocation de mémoire.
         * Il n’est pas pertinent de copier les données, car le résultat serait de toute façon incohérent.
         */
        void resize(int _size)
        {
            delete []m_data;
            m_data = new _Scalar[_size]{ 0 };
            m_size=_size;
        }

        /** Met tous les éléments à zéro */
        void setZero()
        {
            /** TODO: Implémenter. */
            memset(m_data, 0, sizeof(_Scalar) * m_size);
        }

        /** Accès au tampon de données (en lecteur seulement) */
        const _Scalar* data() const {
            return m_data; }

        /** Accès au tampon de données (pour lecture et écriture) */
        _Scalar* data() { 
            return m_data; }
    };

}
